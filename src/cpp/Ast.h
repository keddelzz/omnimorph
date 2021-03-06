#pragma once

#include <cassert>
#include <cstring> // for memset

#include "../data/types.h"
#include "../data/List.h"
#include "../data/StringBuilder.h"

#include "Token.h"

namespace cpp {

// @TODO: type modifiers (signed, unsigned, const, volatile...)

struct NameExp
{
    Token name;
};

enum class PrimitiveExpKind : u8
{
    Invalid,
    Bool,
    Char,
    Double,
    Float,
    Int,
    Long,
    Short,
    Void,
    Wchar_t
};

struct PrimitiveExp
{
    PrimitiveExpKind kind { PrimitiveExpKind::Invalid };
};

enum class ExpKind : u8
{
    Invalid,
    Primitive,
    Name,
};

struct Exp
{
    ExpKind kind { ExpKind::Invalid };

    union {
        PrimitiveExp primitive;
        NameExp      name;
    };
};

enum class Visibility : u8
{
    Invalid,
    Private,
    Protected,
    Public,
};

enum class DeclKind : u8
{
    Invalid,

    Type,
    Field,
    Method
};

struct Decl;

enum class TypeKind : u8
{
    Invalid,
    Class,
    Struct,
    Enum,
    Union,
};

struct TypeDecl
{
    TypeKind kind { TypeKind::Invalid };
    List<Decl *> members;
    bool marked { false };
};

struct FieldDecl
{
    Exp *type { nullptr };
};

struct MethodDecl
{
    Exp *returnType { nullptr };
    List<FieldDecl *> parameters;
};

struct Decl
{
    DeclKind kind { DeclKind::Invalid };
    Visibility visibility;
    Token name;

    union {
        TypeDecl   type;
        FieldDecl  field;
        MethodDecl method;
    };
};

class Ast
{
public:
    constexpr static Exp *allocExp(ExpKind kind, u64 count = 1) { return tag(alloc<Exp>(count), count, kind); }
    constexpr static Decl *allocDecl(DeclKind kind, u64 count = 1) { return tag(alloc<Decl>(count), count, kind); }
    template<typename T>
    constexpr static void freeAst(T *ast) { free(ast); }

    static void showStructure(StringBuilder &buffer, const Exp *exp, int level = 0);
    static void showStructure(StringBuilder &buffer, const Decl *decl, int level = 0);

private:
    static void makeIndentation(StringBuilder &buffer, int level);

    static void showStructure(StringBuilder &buffer, Visibility visibility);
    static void showStructure(StringBuilder &buffer, TypeKind kind);

    static void showStructure(StringBuilder &buffer, const Exp *decl, const PrimitiveExp &primitive, int level);
    static void showStructure(StringBuilder &buffer, const Exp *decl, const NameExp &name, int level);

    static void showStructure(StringBuilder &buffer, const Decl *decl, const TypeDecl &type, int level);
    static void showStructure(StringBuilder &buffer, const Decl *decl, const FieldDecl &field, int level);
    static void showStructure(StringBuilder &buffer, const Decl *decl, const MethodDecl &method, int level);

    template<typename T>
    constexpr static T *alloc(u64 count)
    {
        const auto byteSize = sizeof(T) * count;
        auto vp = malloc(byteSize);
        assert(vp != nullptr);
        memset(vp, 0, byteSize);
        return static_cast<T *>(vp);;
    }

    template<typename T, typename Tag>
    constexpr static T *tag(T *data, u64 count, Tag tag)
    {
        for (auto i = 0; i < count; ++i) {
            data[i].kind = tag;
        }
        return data;
    }

    Ast() = delete;
};

}
