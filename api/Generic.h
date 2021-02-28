#pragma once

#include "HList.h"

#define generic(T) \
    friend class CopyGeneric<T>;

template<typename T>
struct CopyGeneric
{
    using Type = T;
    using Repr = HNil;                           // generated
//  static Repr to(const Type &value);           // generated
//  static Type from(const Repr &repr);          // generated
};
