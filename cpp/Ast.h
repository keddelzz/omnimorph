#pragma once

#include <cassert>
#include <cstring> // for memset

#include "../data/types.h"
#include "../data/List.h"
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
    Name,
    Primitive,
};

struct Exp
{
    ExpKind kind { ExpKind::Invalid };

    union {
        NameExp      nameExp;
        PrimitiveExp primitiveExp;
    };
};

enum class MemberVisibility : u8
{
    Invalid,
    Private,
    Protected,
    Public,
};

struct FieldDecl
{
    MemberVisibility visibility { MemberVisibility::Invalid };
    Exp *type { nullptr };
    Token name;
};

struct MethodDecl
{
    MemberVisibility visibility { MemberVisibility::Invalid };
    Exp *returnType { nullptr };
    Token name;
    List<FieldDecl *> parameters;
};

enum class MemberDeclKind : u8
{
    Invalid,
    Field,
    Method
};

struct MemberDecl
{
    MemberDeclKind kind { MemberDeclKind::Invalid };

    union {
        FieldDecl  fieldDecl;
        MethodDecl methodDecl;
    };
};

enum class TypeDeclKind : u8
{
    Invalid,
    CompoundType,
    EnumType,
    UnionType,
};

struct CompoundTypeDecl
{
    bool isClass; // isClass ? class : struct
    List<MemberDecl *> members;
};

struct EnumTypeDecl
{
    List<MemberDecl *> members;
};

struct UnionTypeDecl
{
    List<MemberDecl *> members;
};

struct TypeDecl
{
    TypeDeclKind kind { TypeDeclKind::Invalid };
    Token name;

    union {
        CompoundTypeDecl compoundType;
        EnumTypeDecl     enumType;
        UnionTypeDecl    unionType;
    };
};

class Ast
{
public:
    constexpr static Exp *allocExp(ExpKind kind, u64 count = 1) { return tag(alloc<Exp>(count), count, kind); }
    constexpr static MemberDecl *allocMemberDecl(MemberDeclKind kind, u64 count = 1) { return tag(alloc<MemberDecl>(count), count, kind); }
    constexpr static TypeDecl *allocTypeDecl(TypeDeclKind kind, u64 count = 1) { return tag(alloc<TypeDecl>(count), count, kind); }
    template<typename T>
    constexpr static void freeAst(T *ast) { free(ast); }

private:
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
