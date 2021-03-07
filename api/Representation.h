#pragma once

#include "HList.h"

template<typename T>
struct Named
{
    explicit Named(const char *name, T value)
        : name(name)
        , value(value)
    {}

    const char *name;
    T value;
};
