#include "CppParser.h"

#include "../data/ScopeGuard.h"

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

void CppParser::foreachToplevelDeclaration(std::function<IterationDecision(Decl *)> consumer)
{
    const auto isDone = [this]() {
        return scanner.peek().type == TokenType::Eof or
               scanner.peek().type == TokenType::Error;
    };

    List<Decl *> toplevelDecl;
    if (not parseDecls(toplevelDecl)) {
        return;
    }
    for (auto i = 0; i < toplevelDecl.length; ++i) {
        auto decl = toplevelDecl[i];

        switch (consumer(decl)) {
            case IterationDecision::Continue: continue;
            case IterationDecision::Break: goto end;
        }
    }
    end:

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
            exp->name.name = scanner.drop();
            return exp;
        } else {
            scanner.drop();
            auto exp = Ast::allocExp(ExpKind::Primitive);
            exp->primitive.kind = kind;
            return exp;
        }
    }

    return nullptr;
}

u16 CppParser::detectTypeMarker(const String &typeName)
{
    // generic (T)

    u16 offset = 0;
    const auto skipWhitespace = [&]() {
        while (isWhitespace(scanner.peek(offset))) ++offset;
    };

    {
        const auto &ident = scanner.peek(offset);
        if (TokenType::Ident != ident.type)
            return 0;
        ++offset;
        skipWhitespace();

        const String generic("generic");
        if (generic != ident.lexeme.toString())
            return 0;
    }

    const auto &oparen = scanner.peek(offset);
    if (TokenType::Sym_OpenParen != oparen.type)
        return 0;
    ++offset;
    skipWhitespace();

    {
        const auto &name = scanner.peek(offset);
        // @TODO: allow type specializations?
        if (TokenType::Ident != name.type)
            return 0;
        ++offset;
        skipWhitespace();

        if (typeName != name.lexeme.toString())
            return 0;
    }

    const auto &cparen = scanner.peek(offset);
    if (TokenType::Sym_CloseParen != cparen.type)
        return 0;
    ++offset;

    return offset;
}

void CppParser::skipPreprocessorStatement()
{
    assert(TokenType::Sym_Hash == scanner.peek().type);

    dropUntil(isWhitespaceContainingLinebreak);
    scanner.drop(); // <white>
};

Visibility CppParser::parseVisibilityBlock()
{
    const auto ok = [this](Visibility visibility) -> Visibility {
        scanner.drop(); // private, protected, public

        const auto &colon = scanner.peek();
        requireType(colon, TokenType::Sym_Colon, Visibility::Invalid);
        scanner.drop(); // :

        dropWhile(isWhitespace);

        return visibility;
    };

    switch (scanner.peek().type) {
        case TokenType::Kw_private  : return ok(Visibility::Private);
        case TokenType::Kw_protected: return ok(Visibility::Protected);
        case TokenType::Kw_public   : return ok(Visibility::Public);
        // @TODO: Support Qt's signals: public/private slots:
        default                     : return Visibility::Invalid;
    }
}

Decl *CppParser::parseCompoundMember()
{
    dropWhile(isWhitespace);

    if (not canBeTpt())
        return nullptr;

    auto tpt = parseTpt();
    dropWhile(isWhitespace);

    EnabledScopeGuard freeTpt = [&]() {
        if (tpt != nullptr) Ast::freeAst(tpt);
    };

    auto name = scanner.drop();
    requireType(name, TokenType::Ident, nullptr);
    dropWhile(isWhitespace);

    const auto acceptField = [&]() -> Decl * {
        auto decl = Ast::allocDecl(DeclKind::Field);
        decl->name = name;
        decl->visibility = context.peek().visibility;

        auto &field = decl->field;
        field.type = tpt;
        freeTpt.disable();

        return decl;
    };

    switch (scanner.peek().type) {
        // <tpt> <ident> ;
        case TokenType::Sym_Semicolon: {
            scanner.drop(); // ;
            dropWhile(isWhitespace);

            return acceptField();
        }

        // <tpt> <ident> = <exp> ;
        case TokenType::Sym_Equal: {
            scanner.drop(); // =
            // Drop initializer
            dropWhile(noSemicolon);

            scanner.drop(); // ;
            dropWhile(isWhitespace);

            return acceptField();
        }

        // <tpt> <ident> { <exp>, ... } ;
        case TokenType::Sym_OpenCurly: {
            scanner.drop(); // {
            // Drop initializer-list
            dropUntil(isCloseCurly);
            dropWhile(isWhitespace);

            requireType(scanner.peek(), TokenType::Sym_Semicolon, nullptr)
            scanner.drop(); // ;
            dropWhile(isWhitespace);

            return acceptField();
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

Decl *CppParser::parseCompoundTypeDecl(NamespaceType namespaceType)
{
    assert(isCompoundLike(namespaceType));

    scanner.drop(); // struct, class, union
    dropWhile(isWhitespace);

    auto name = scanner.drop();
    requireType(name, TokenType::Ident, nullptr);
    dropWhile(isWhitespace);

    auto decl = Ast::allocDecl(DeclKind::Type);
    decl->visibility = context.peek().visibility;
    decl->name = name;
    EnabledScopeGuard freeDecl = [&]() { Ast::freeAst(decl); };

    {
        NamespaceElement element;
        if (isCompound(namespaceType)) {
            element.visibility = NamespaceType::Class == namespaceType
                ? Visibility::Private
                : Visibility::Public;
        } else {
            element.visibility = Visibility::Public;
        }
        element.namespaceType = namespaceType;
        element.elementName = name;

        context.push(element);
    }
    ScopeGuard popContext = [this]() { context.pop(); };

    auto &type = decl->type;
    switch (namespaceType) {
        case NamespaceType::Class:  type.kind = TypeKind::Class; break;
        case NamespaceType::Struct: type.kind = TypeKind::Struct; break;
        case NamespaceType::Union:  type.kind = TypeKind::Union; break;
        default: assert(false && "Should be handled by previous assert!"); break;
    }

    requireType(scanner.peek(), TokenType::Sym_OpenCurly, nullptr);
    scanner.drop(); // {
    dropWhile(isWhitespace);

    // @TODO: Don't only require the user to use the marker after class <name> {
    auto typeMarkerOffset = detectTypeMarker(name.lexeme.toString());
    if (typeMarkerOffset > 0) {
        type.marked = true;

        scanner.drop(typeMarkerOffset);
        dropWhile(isWhitespace);
    }

    if (not parseDecls(type.members))
        return nullptr;

    dropWhile(isWhitespace);

    requireType(scanner.peek(), TokenType::Sym_CloseCurly, nullptr);
    scanner.drop(); // }
    dropWhile(isWhitespace);

    requireType(scanner.peek(), TokenType::Sym_Semicolon, nullptr);
    scanner.drop(); // ;
    dropWhile(isWhitespace);

    freeDecl.disable();

    return decl;
}

bool CppParser::canBeDecl()
{
    switch (scanner.peek().type) {
        case TokenType::Kw_class : return true;
        case TokenType::Kw_struct: return true;
        case TokenType::Kw_union : return true;
        case TokenType::Kw_enum  : return true;
        default                  : return canBeTpt();
    }
}

Decl *CppParser::parseDecl()
{
    // @TODO: Parse constructors

    switch (scanner.peek().type) {
        case TokenType::Kw_class : return parseCompoundTypeDecl(NamespaceType::Class);
        case TokenType::Kw_struct: return parseCompoundTypeDecl(NamespaceType::Struct);
        case TokenType::Kw_union : return parseCompoundTypeDecl(NamespaceType::Union);
        case TokenType::Kw_enum  : assert(false && "Unimplemented"); return nullptr;
        default                  :
            if (canBeTpt()) return parseCompoundMember();
            return nullptr;
    }
}

bool CppParser::parseDecls(List<Decl *> &members)
{
    while (true) {
        const auto &token = scanner.peek();
        if (TokenType::Eof == token.type) break;
        if (TokenType::Error == token.type) break;

        while (TokenType::Sym_Hash == scanner.peek().type) {
            dropWhile(isWhitespace);
            skipPreprocessorStatement();
        }

        dropWhile(isWhitespace);

        auto visibility = Visibility::Invalid;
        do {
            visibility = parseVisibilityBlock();
            if (Visibility::Invalid != visibility) {
                auto &elem = context.peek();
                elem.visibility = visibility;
            }
        } while (Visibility::Invalid != visibility);

        dropWhile(isWhitespace);

        if (not canBeDecl()) break;

        auto t = parseDecl();
        if (t == nullptr) break;

        members.append(t);
    }

    return true;
}

}
