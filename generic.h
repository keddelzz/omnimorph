#pragma once

#include "flatfunction.h"

template<typename T>
struct Generic
{
    using Type = T;
    using Repr = int; // generated
    FlatFunction to;
    FlatFunction from;
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
    return generic.to.template operator()<Type, const Repr &>(value);
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
    return generic.from.template operator()<Repr, const Type &>(repr);
}

template<typename T>
typename Generic<T>::Type to_value(
    const typename Generic<T>::Repr &repr)
{
    return to_value<T>(Generic<T>(), repr);
}
