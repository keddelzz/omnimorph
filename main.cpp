#include <iostream>
#include <functional>

#include "flatfunction.h"
#include "hlist.h"
#include "generic.h"
#include "testdata.h"

template<template<typename ...> class C, typename... T>
class HasShow
{
    struct yes {};
    struct no { char x[2]; };

    template<template<typename ...> class C0, typename... T0>
    static yes test( decltype(&C0<T0 ...>::show) ) ;
    template<template<typename ...> class C0, typename... T0>
    static no test(...);

public:
    enum { value = sizeof(test<C, T ...>(nullptr)) == sizeof(yes) };
};

// show primitives
template<typename T, typename = std::enable_if<false>>
struct ShowP {
//    static std::string show(T); // no implementation
};
template<>
struct ShowP<int, void> {
    static std::string show(int value) { return std::to_string(value); }
};
template<>
struct ShowP<bool, void> {
    static std::string show(bool value) { return value ? "true" : "false"; }
};
template<>
struct ShowP<const char *, void> {
    static std::string show(const char *value) { return std::string(value); }
};
template<>
struct ShowP<std::string, void> {
    static std::string show(std::string value) { return value; }
};

// user defined
template<typename T, typename = std::enable_if<false>>
struct ShowU {
//    static std::string show(T); // no implementation
};
// no specialization

// leveraging generic repr
template<typename T, typename = std::enable_if<false>>
struct ShowG {
//    static std::string show(T); // no implementation
};

// forwarder
template<typename T, typename = std::enable_if<false>>
struct Show {
//    static std::string show(T); // no implementation
};
template<typename T> // always prefer primitive show instances
struct Show<T, typename std::enable_if<
        HasShow<ShowP, T, void>::value
        >::type> {
    static std::string show(T value) { return ShowP<T, void>::show(value); }
};
template<typename T> // if no primitive exists, prefer user defined instance over generic
struct Show<T, typename std::enable_if<
        !HasShow<ShowP, T, void>::value and
         HasShow<ShowU, T, void>::value
        >::type> {
    static std::string show(T value) { return ShowU<T, void>::show(value); }
};
template<typename T> // else use generic repr
struct Show<T, typename std::enable_if<
        !HasShow<ShowP, T, void>::value and
        !HasShow<ShowU, T, void>::value and
         HasShow<ShowG, T, void>::value
        >::type> {
    static std::string show(T value) { return ShowG<T, void>::show(value); }
};

template<>
struct ShowG<HNil, void> {
    static std::string show(HNil) { return "HNil"; }
};
template<typename H, typename T>
struct ShowG<HList<H, T>, void> {
    static std::string show(HList<H, T> value) {
        using ShowH = Show<H, void>;
        using ShowT = Show<T, void>;
        return ShowH::show(value.head) + " :: " + ShowT::show(value.tail);
    };
};
template<typename T>
struct ShowG<T, void> {
    static std::string show(T value) {
        Generic<T> gen;
        using ShowRepr = Show<typename Generic<T>::Repr, void>;
        return "(" + ShowRepr::show(to_repr(gen, value)) + ")";
    };
};

template<typename T>
std::string show(T value) {
    return Show<T, void>::show(value);
}

int main() {
    struct Kek {};

    const char *streetName = "Nullptr Street";
    const char *name = "Simon Segfault";
    SimpleAddress a(streetName, 32);
    TestPerson p(name, a, 55);

    std::cout
        << show(42) << std::endl
        << show<std::string>("asd") << std::endl
        << show<HNil>({}) << std::endl
        << show(TestPerson_Repr_2(42, {})) << std::endl
//        << show<Kek>({}) << std::endl
        << show(p) << std::endl
        << "the end" << std::endl
        ;
}

// @TODO: Generalize HasShow for other type classes
// @TODO: Try to get rid of fake type parameter (void)
// @TODO: Try out inductive datastructures
// @TODO: Going constexpr

int main2() {
    constexpr const char *meh = "meh";
    auto test = hlist(1, 2, std::string(meh));
    std::cout << hlist() << std::endl;
    std::cout << test << std::endl;

    const char *streetName = "New Years Street";
    const char *name = "Peter Finger";
    SimpleAddress a(streetName, 32);
    TestPerson p(name, a, 55);

    auto x = to_repr<TestPerson>(p);
    auto b = to_value<TestPerson>(x);
    return 0;
}
