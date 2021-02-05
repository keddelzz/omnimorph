#pragma once

#include "grepr.h"

template<typename T>
struct Generic
{
    using Type    = T;
    using Members = int; // generated
    using Repr    = Class<T, Members>;
//  static Repr to(const Type & value);
//  static Type from(const Repr &repr);
};
