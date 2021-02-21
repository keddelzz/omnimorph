#pragma once

#include "../data/types.h"
#include "../data/List.h"

#include "CppScanner.h"
#include "Lookahead.h"
#include "Ast.h"

namespace cpp {

class CppParser
{

public:
    explicit CppParser();
    ~CppParser();
    void initialize(const String &filePath, const String &fileContents);

    void foreachTypeDefinition(Consumer<TypeDecl *> consumer);

private:
    union {;
        String filePath;
    };

    bool parseError { false };

    template<u64 maxLookahead>
    using LookaheadScanner = Lookahead<CppScanner, Token, maxLookahead>;
    LookaheadScanner<16> scanner;

    template<typename Predicate>
    inline void dropWhile(Predicate p)
    {
        while (p(scanner.peek()))
            scanner.drop();
    }

    constexpr static inline bool isWhitespace(const Token &token) { return TokenType::White == token.type; }
    constexpr static inline bool isSemicolon(const Token &token) { return TokenType::Sym_Semicolon == token.type; }
    constexpr static inline bool isCloseCurly(const Token &token) { return TokenType::Sym_Semicolon == token.type; }

    template<typename T, typename ParseSingle, typename Predicate>
    inline bool parseListWhile(List<T *> &list, ParseSingle parse, Predicate p)
    {
        while (true) {
            const auto &token = scanner.peek();
            if (TokenType::Eof == token.type) break;
            if (TokenType::Error == token.type) break;
            if (not p(token)) break;

            auto t = parse();
            if (t == nullptr) break;
            list.append(t);
        }
        return true;
    }
    template<typename T, typename ParseSingle, typename Predicate>
    inline bool parseListUntil(List<T *> &list, ParseSingle parse, Predicate p)
    {
        while (true) {
            const auto &token = scanner.peek();
            if (TokenType::Eof == token.type) break;
            if (TokenType::Error == token.type) break;
            if (p(token)) break;

            auto t = parse();
            if (t == nullptr) break;
            list.append(t);
        }
        return true;
    }

    bool canBeTpt() { return canBeExp(); }
    Exp *parseTpt() { return parseExp(); }
    bool canBeExp();
    Exp *parseExp();

    MemberVisibility parseVisibilityBlock();
    enum class CompoundTypeType : u8
    { Class, Struct, Union };
    struct TypeDeclContext
    {
        CompoundTypeType type;
        MemberVisibility visibility { MemberVisibility::Invalid };
    };
    MemberDecl *parseCompoundMember(TypeDeclContext &context);
    bool parseCompoundMembers(TypeDeclContext &context, List<MemberDecl *> &members);
    TypeDecl *parseEnumTypeDecl();
    TypeDecl *parseCompoundTypeDecl(CompoundTypeType context);
    TypeDecl *parseTypeDecl();

};

}
