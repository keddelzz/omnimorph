#pragma once

#include "../data/types.h"
#include "../data/IterationDecision.h"
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

    void foreachToplevelDeclaration(std::function<IterationDecision(Decl *)> consumer);

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

    MemberVisibility parseVisibilityBlock();
    enum class NamespaceType : u8
    {
        Invalid,
        Namespace,
        Class,
        Struct,
        Union
    };
    static bool isCompoundLike(NamespaceType type)
    {
        switch (type) {
            case NamespaceType::Class : return true;
            case NamespaceType::Struct: return true;
            case NamespaceType::Union : return true;
            default                   : return false;
        }
    }
    static bool isCompound(NamespaceType type)
    {
        switch (type) {
            case NamespaceType::Class : return true;
            case NamespaceType::Struct: return true;
            default                   : return false;
        }
    }
    struct NamespaceElement
    {
        MemberVisibility visibility { MemberVisibility::Invalid };
        NamespaceType namespaceType { NamespaceType::Invalid };
        Token elementName;
    };
    struct ParseContext
    {
        explicit ParseContext()
        {
            NamespaceElement element;
            element.visibility = MemberVisibility::Public;
            element.namespaceType = NamespaceType::Namespace;
            element.elementName = Token(); // mark as top level
            stack.append(element);
        }

        void push(const NamespaceElement &element)
        {
            stack.append(element);
        }

        const NamespaceElement &peek() const
        {
            return stack[stack.length - 1];
        }
        NamespaceElement &peek()
        {
            return stack[stack.length - 1];
        }

        NamespaceElement pop()
        {
            const auto elem = peek();
            --stack.length;
            return elem;
        }

        List<NamespaceElement> stack;
    };

    ParseContext context;

    bool canBeTpt() { return canBeExp(); }
    Exp *parseTpt() { return parseExp(); }
    bool canBeExp();
    Exp *parseExp();

    bool canBeDecl();
    Decl *parseCompoundMember();
    Decl *parseCompoundTypeDecl(NamespaceType namespaceType);
    Decl *parseDecl();
    bool parseDecls(List<Decl *> &members);

};

}
