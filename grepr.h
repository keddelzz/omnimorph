#pragma once

#include "hlist.h"
#include "flatpointer.h"

template<typename T, typename Members>
class Class {
public:
    constexpr explicit Class(
        const char *name
        , FlatPointer base
        , Members members)
        : name(name)
        , base(base)
        , members(members)
    {}

    const char  *name;
    FlatPointer base;
    Members     members;
};

template<typename T>
class Member {
public:
    constexpr Member(const char *name, FlatPointer offset)
        : name(name)
        , offset(offset)
    {}

    const char  *name;
    FlatPointer offset;

    constexpr T *of(FlatPointer base) const {
        return (T *)(base + offset);
    }
};

template <class T, class M> M type_of_member_inference_helper(M T:: *);
#define type_of_member_pointer(mem) decltype(type_of_member_inference_helper(mem))
#define type_of_member(Type, name) type_of_member_pointer(&Type::name)
#define member_of(Type, name) Member<type_of_member(Type, name)>(#name, FlatPointer(offsetof(Type, name)))
