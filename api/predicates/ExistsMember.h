#pragma once

#define GENERATE_EXISTS_MEMBER_0_CONCEPTS(predicate_name, member_name)        \
    template<typename C>                                                      \
    concept predicate_name = requires {                                       \
        C::member_name;                                                       \
    };

#define GENERATE_EXISTS_MEMBER_0_NO_CONCEPTS(predicate_name, member_name)     \
    template<typename C>                                                      \
    class predicate_name##_helper                                             \
    {                                                                         \
        struct yes {};                                                        \
        struct no { char x[2]; };                                             \
                                                                              \
        template<typename C0>                                                 \
        static yes test( decltype(&C0::member_name) ) { return {}; }          \
        template<typename C0>                                                 \
        static no test(...) { return {}; }                                    \
                                                                              \
    public:                                                                   \
        enum { value = sizeof(test<C>(nullptr)) == sizeof(yes) };             \
    };                                                                        \
                                                                              \
    template<typename C>                                                      \
    constexpr bool predicate_name = predicate_name##_helper<C>::value;

#ifdef __cpp_concepts
#define GENERATE_EXISTS_MEMBER_0(predicate_name, member_name)                 \
    GENERATE_EXISTS_MEMBER_0_CONCEPTS(predicate_name, member_name)
#else
#define GENERATE_EXISTS_MEMBER_0(predicate_name, member_name)                 \
    GENERATE_EXISTS_MEMBER_0_NO_CONCEPTS(predicate_name, member_name)
#endif

#define GENERATE_EXISTS_MEMBER_1_CONCEPTS(predicate_name, member_name)        \
    template<template<typename ...> class C, typename... T>                   \
    concept predicate_name = requires {                                       \
        C<T ...>::member_name;                                                \
    };

#define GENERATE_EXISTS_MEMBER_1_NO_CONCEPTS(predicate_name, member_name)     \
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
    constexpr bool predicate_name = predicate_name##_helper<C, T ...>::value;

#ifdef __cpp_concepts
#define GENERATE_EXISTS_MEMBER_1(predicate_name, member_name)                 \
    GENERATE_EXISTS_MEMBER_1_CONCEPTS(predicate_name, member_name)
#else
#define GENERATE_EXISTS_MEMBER_1(predicate_name, member_name)                 \
    GENERATE_EXISTS_MEMBER_1_NO_CONCEPTS(predicate_name, member_name)
#endif
