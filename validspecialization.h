#pragma once

template<template<typename ...> class C, typename... T>
struct ValidSpecialization {
    typedef struct { char _; } yes;
    typedef struct { yes _[2]; } no;

    template<template<typename...> class D>
    static yes test(D<T...>*);

    template<template<typename...> class D>
    static no test(...);

    constexpr static bool value = (sizeof(test<C>(0)) == sizeof(yes));
};