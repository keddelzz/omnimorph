#pragma once

template<typename T>
struct Generic
{
    using Type = T;
    using Repr = int; // generated
//  static Repr to(const Type & value);
//  static Type from(const Repr &repr);
};

template<typename T>
class Class {
public:
    constexpr explicit Class(const char *name, T value)
        : name(name)
        , value(value)
    {}

    const char *name;
    T          value;
};

template<typename T>
class Member {
public:
    constexpr Member(const char *name, T value)
        : name(name)
        , value(value)
    {}

    const char *name;
    T           value;
};
