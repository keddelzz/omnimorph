#pragma once

#include "hlist.h"

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
