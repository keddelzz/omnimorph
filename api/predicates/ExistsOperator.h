#pragma once

#include <type_traits>
#include <ostream>

#include "DependentVoid.h"

#define GENERATE_EXISTS_OPERATOR(predicate_name, op)                  \
template<typename, typename, typename = void>                         \
struct predicate_name##_helper                                        \
    : std::false_type                                                 \
{};                                                                   \
template<typename A, typename B>                                      \
struct predicate_name##_helper<A, B, DependentVoid<                   \
        decltype(std::declval<A>() op std::declval<B>())              \
        >>                                                            \
    : std::true_type                                                  \
{};                                                                   \
template<typename A, typename B>                                      \
constexpr bool predicate_name = predicate_name##_helper<A, B>::value;
