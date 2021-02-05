#pragma once

#define GENERATE_HAS_STATIC_METHOD_CONCEPTS(predicate_name, member_name)      \
    template<template<typename ...> class C, typename... T>                   \
    concept predicate_name = requires {                                       \
        C<T ...>::member_name;                                                \
    };

#define GENERATE_HAS_STATIC_METHOD_NO_CONCEPTS(predicate_name, member_name)   \
    template<template<typename ...> class C, typename... T>                   \
    class predicate_name##_helper                                             \
    {                                                                         \
        struct yes {};                                                        \
        struct no { char x[2]; };                                             \
                                                                              \
        template<template<typename ...> class C0, typename... T0>             \
        static yes test( decltype(&C0<T0 ...>::member_name) ) { return {}; }  \
        template<template<typename ...> class C0, typename... T0>             \
        static no test(...) { return {}; }                                    \
                                                                              \
    public:                                                                   \
        enum { value = sizeof(test<C, T ...>(nullptr)) == sizeof(yes) };      \
    };                                                                        \
                                                                              \
    template<template<typename ...> class C, typename... T>                   \
    constexpr auto predicate_name = predicate_name##_helper<C, T ...>::value;

#ifdef __cpp_concepts
#define GENERATE_HAS_STATIC_METHOD(predicate_name, member_name)               \
    GENERATE_HAS_STATIC_METHOD_CONCEPTS(predicate_name, member_name)
#else
#define GENERATE_HAS_STATIC_METHOD(predicate_name, member_name)               \
    GENERATE_HAS_STATIC_METHOD_NO_CONCEPTS(predicate_name, member_name)
#endif
