#pragma once

#include "flatfunction.h"

template<typename T>
struct Generic
{
    using Type = T;
    using Repr = int; // generated
    FlatFunction<const Type &, Repr> to;
    FlatFunction<const Repr &, Type> from;
};

template<typename T>
constexpr Generic<T> generic();

template<typename T>
typename Generic<T>::Repr to_repr(
    const Generic<T> &generic,
    const typename Generic<T>::Type &value)
{
    using Type = typename Generic<T>::Type;
    using Repr = typename Generic<T>::Repr;
    return generic.to(value);
}

template<typename T>
typename Generic<T>::Repr to_repr(
    const typename Generic<T>::Type &value)
{
    return to_repr<T>(Generic<T>(), value);
}

template<typename T>
typename Generic<T>::Type to_value(
    const Generic<T> &generic,
    const typename Generic<T>::Repr &repr)
{
    using Repr = typename Generic<T>::Repr;
    using Type = typename Generic<T>::Type;
    return generic.from(repr);
}

template<typename T>
typename Generic<T>::Type to_value(
    const typename Generic<T>::Repr &repr)
{
    return to_value<T>(Generic<T>(), repr);
}

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
