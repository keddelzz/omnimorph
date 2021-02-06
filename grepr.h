#pragma once

#include "hlist.h"
#include "flatpointer.h"

template<typename T>
class MemberValue
{
public:
    constexpr MemberValue(const char *name, T value)
        : name(name)
        , value(value)
    {}

    const char  *name;
    T           value;
};

#define member_value(value, member) MemberValue(#member, value.member)

template<typename T>
class MemberReference
{
public:
    constexpr MemberReference(const char *name, T &ref)
       : name(name)
       , ref(ref)
    {}

    const char  *name;
    T           &ref;
};

#define member_reference(value, member) MemberReference(#member, value.member)

template<typename T>
class MemberPointer
{
public:
    constexpr MemberPointer(const char *name, T *pointer)
       : name(name)
       , pointer(pointer)
    {}

    const char  *name;
    T           *pointer;
};

#define member_pointer(value, member) MemberPointer(#member, &value.member)

template <class T, class M> M type_of_member_inference_helper(M T:: *);
#define type_of_member_pointer(mem) decltype(type_of_member_inference_helper(mem))
#define type_of_member(Type, name) type_of_member_pointer(&Type::name)
#define member_of(Type, name) MemberPointer<type_of_member(Type, name)>(#name, FlatPointer(offsetof(Type, name)))
