#include "CppParser.h"

#include <iostream>

namespace cpp {

#define requireType(token, expectedType, ret)      \
    do {                                           \
        if (parseError) return (ret);              \
        if ((token).type != expectedType) {        \
            parseError = true;                     \
            std::cout                              \
                << "Expected token of type '"      \
                << (expectedType) << "' but got '" \
                << (token).type << "'!"            \
                << std::endl ;                     \
            return (ret);                          \
        }                                          \
    } while (0);

CppParser::CppParser()
{}

CppParser::~CppParser()
{}

void CppParser::initialize(const String &filePath, const String &fileContents)
{
    this->filePath = filePath;
    scanner.underlying().initialize(filePath, fileContents);
}

void CppParser::foreachTypeDefinition(Consumer<TypeDecl *>)
{
    const auto isDone = [this]() {
        return scanner.peek().type == TokenType::Eof or
               scanner.peek().type == TokenType::Error;
    };

    auto decl = parseTypeDecl();

    while (not isDone()) {
        std::cout << scanner.drop() << std::endl;
    }
    std::cout << scanner.peek() << std::endl;
}

bool CppParser::canBeExp()
{
    switch (scanner.peek().type) {
        case TokenType::Ident     : return true;
        case TokenType::Kw_bool   : return true;
        case TokenType::Kw_char   : return true;
        case TokenType::Kw_double : return true;
        case TokenType::Kw_float  : return true;
        case TokenType::Kw_int    : return true;
        case TokenType::Kw_long   : return true;
        case TokenType::Kw_short  : return true;
        case TokenType::Kw_void   : return true;
        case TokenType::Kw_wchar_t: return true;
        default                   : return false;
    }
}

Exp *CppParser::parseExp()
{
    auto isIdent = false;
    auto kind = PrimitiveExpKind::Invalid;

    switch (scanner.peek().type) {
        case TokenType::Ident     : isIdent = true; break;
        case TokenType::Kw_bool   : isIdent = true; kind = PrimitiveExpKind::Bool; break;
        case TokenType::Kw_char   : isIdent = true; kind = PrimitiveExpKind::Char; break;
        case TokenType::Kw_double : isIdent = true; kind = PrimitiveExpKind::Double; break;
        case TokenType::Kw_float  : isIdent = true; kind = PrimitiveExpKind::Float; break;
        case TokenType::Kw_int    : isIdent = true; kind = PrimitiveExpKind::Int; break;
        case TokenType::Kw_long   : isIdent = true; kind = PrimitiveExpKind::Long; break;
        case TokenType::Kw_short  : isIdent = true; kind = PrimitiveExpKind::Short; break;
        case TokenType::Kw_void   : isIdent = true; kind = PrimitiveExpKind::Void; break;
        case TokenType::Kw_wchar_t: isIdent = true; kind = PrimitiveExpKind::Wchar_t; break;
        default                   : break;
    }

    if (isIdent) {
        if (PrimitiveExpKind::Invalid == kind) {
            auto exp = Ast::allocExp(ExpKind::Name);
            exp->nameExp.name = scanner.drop();
            return exp;
        } else {
            scanner.drop();
            auto exp = Ast::allocExp(ExpKind::Primitive);
            exp->primitiveExp.kind = kind;
            return exp;
        }
    }

    return nullptr;
}

MemberVisibility CppParser::parseVisibilityBlock()
{
    const auto ok = [this](MemberVisibility visibility) -> MemberVisibility {
        scanner.drop(); // private, protected, public

        const auto &colon = scanner.peek();
        requireType(colon, TokenType::Sym_Colon, MemberVisibility::Invalid);
        scanner.drop(); // :

        return visibility;
    };

    switch (scanner.peek().type) {
        case TokenType::Kw_private  : return ok(MemberVisibility::Private);
        case TokenType::Kw_protected: return ok(MemberVisibility::Protected);
        case TokenType::Kw_public   : return ok(MemberVisibility::Public);
        // @TODO: Support Qt's signals: public/private slots:
        default                     : return MemberVisibility::Invalid;
    }
}

MemberDecl *CppParser::parseCompoundMember(TypeDeclContext &context)
{
    dropWhile(isWhitespace);

    const auto visibilityBlock = parseVisibilityBlock();
    if (MemberVisibility::Invalid != visibilityBlock) {
        context.visibility = visibilityBlock;
    }
    dropWhile(isWhitespace);

    if (not canBeTpt())
        return nullptr;

    auto tpt = parseTpt();
    dropWhile(isWhitespace);

    auto name = scanner.drop();
    requireType(name, TokenType::Ident, nullptr);
    dropWhile(isWhitespace);

    switch (scanner.peek().type) {
        // <tpt> <ident> ;
        case TokenType::Sym_Semicolon: {
            scanner.drop();

            auto decl = Ast::allocMemberDecl(MemberDeclKind::Field);
            auto &field = decl->fieldDecl;

            field.visibility = context.visibility;
            field.type = tpt;
            field.name = name;
            return decl;
        }

        // <tpt> <ident> = <exp> ;
        case TokenType::Sym_Equal: {
            assert(false && "Unimplemented");
            return nullptr;
        }

        // <tpt> <ident> { <exp>, ... } ;
        case TokenType::Sym_OpenCurly: {
            assert(false && "Unimplemented");
            return nullptr;
        }

        // <tpt> <ident> ( <param>, ... ) ;
        case TokenType::Sym_OpenParen: {
            assert(false && "Unimplemented");
            return nullptr;
        }

        default: {
            return nullptr;
        }
    }
}

bool CppParser::parseCompoundMembers(TypeDeclContext &context, List<MemberDecl *> &members)
{
    const auto parse = [&, this]() { return parseCompoundMember(context); };
    return parseListUntil(members, parse, isCloseCurly);
}

TypeDecl *CppParser::parseCompoundTypeDecl(CompoundTypeType compoundTypeType)
{
    TypeDeclContext context { .type = compoundTypeType };

    scanner.drop(); // struct, class, union
    dropWhile(isWhitespace);

    const auto typeDeclKind = CompoundTypeType::Union == context.type
        ? TypeDeclKind::UnionType
        : TypeDeclKind::CompoundType;
    auto result = Ast::allocTypeDecl(typeDeclKind); // @Leak

    if (TypeDeclKind::CompoundType == typeDeclKind) {
        const auto isClass = CompoundTypeType::Class == context.type;
        result->compoundType.isClass = isClass;
        context.visibility = isClass
            ? MemberVisibility::Private
            : MemberVisibility::Public;
    }

    result->name = scanner.drop();
    requireType(result->name, TokenType::Ident, nullptr);
    dropWhile(isWhitespace);

    requireType(scanner.peek(), TokenType::Sym_OpenCurly, nullptr);
    scanner.drop(); // {
    dropWhile(isWhitespace);

    auto &members = CompoundTypeType::Union == context.type
        ? result->unionType.members
        : result->compoundType.members;
    if (not parseCompoundMembers(context, members))
        return nullptr;

    dropWhile(isWhitespace);
    requireType(scanner.peek(), TokenType::Sym_CloseCurly, nullptr);
    scanner.drop(); // }

    dropWhile(isWhitespace);
    requireType(scanner.peek(), TokenType::Sym_Semicolon, nullptr);
    scanner.drop(); // ;
    dropWhile(isWhitespace);

    return result;
}

TypeDecl *CppParser::parseEnumTypeDecl()
{
    assert(false && "Unimplemented");
    return nullptr;
}

TypeDecl *CppParser::parseTypeDecl()
{
    switch (scanner.peek().type) {
        case TokenType::Kw_class : return parseCompoundTypeDecl(CompoundTypeType::Class);
        case TokenType::Kw_struct: return parseCompoundTypeDecl(CompoundTypeType::Struct);
        case TokenType::Kw_union : return parseCompoundTypeDecl(CompoundTypeType::Union);
        case TokenType::Kw_enum  : return parseEnumTypeDecl();
        default                  : return nullptr;
    }
}

}
