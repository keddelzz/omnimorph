#pragma once

template<typename T>
struct Generic
{
    using Type = T;
    using Repr = int; // generated
//  static Repr to(const Type & value);
//  static Type from(const Repr &repr);
};
