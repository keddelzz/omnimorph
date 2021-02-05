#include <iostream>
#include <vector>

#include "generic.h"
#include "grepr.h"
#include "testdata.h"
#include "hasmember.h"

GENERATE_HAS_STATIC_METHOD(HasShow, show)

template<typename T, typename = std::enable_if<false>>
struct ShowP {
//  Intentionally commented out
//  static std::string show(T) { return std::string(); }
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

template<typename T, typename = std::enable_if<false>>
struct ShowU {
//  Intentionally commented out
//  static std::string show(T); // no implementation
};

template<typename T, typename = std::enable_if<false>>
struct ShowG {
//  Intentionally commented out
//  static std::string show(T); // no implementation
};

// forwarder
template<typename T, typename = std::enable_if<false>>
struct ShowFwd {
//  static std::string show(T); // no implementation
};
template<typename T> // always prefer primitive show instances
struct ShowFwd<T, typename std::enable_if<
        HasShow<ShowP, T, void>
        >::type> {
    static std::string show(T value) { return ShowP<T, void>::show(value); }
};
template<typename T> // if no primitive exists, prefer user defined instance over generic
struct ShowFwd<T, typename std::enable_if<
        !HasShow<ShowP, T, void> and
         HasShow<ShowU, T, void>
        >::type> {
    static std::string show(T value) { return ShowU<T, void>::show(value); }
};
template<typename T> // else use generic repr
struct ShowFwd<T, typename std::enable_if<
        !HasShow<ShowP, T, void> and
        !HasShow<ShowU, T, void> and
         HasShow<ShowG, T, void>
        >::type> {
    static std::string show(T value) { return ShowG<T, void>::show(value); }
};

template<typename T>
using Show = ShowFwd<T, void>;

template<typename T, typename Ms, typename List>
void show_class_members(Class<T, Ms> &, std::string &, bool first, List list);
template<typename T, typename Ms>
void show_class_members(Class<T, Ms> &, std::string &, bool, HNil) {}
template<typename T, typename Ms, typename Hd, typename Tl>
void show_class_members(Class<T, Ms> &cls, std::string &string, bool first, HList<Member<Hd>, Tl> list) {
    if (not first) string.append(", ");
    const auto &member = list.head;
    string.append(member.name);
    string.append("=");
    auto member_pointer = member.of(cls.base);
    string.append(Show<Hd>::show(*member_pointer));
    show_class_members(cls, string, false, list.tail);
}

template<typename T, typename Ms>
struct ShowG<Class<T, Ms>, void> {
    static std::string show(Class<T, Ms> clazz) {
        std::string result(clazz.name);
        result.append("(");
        show_class_members(clazz, result, true, clazz.members);
        result.append(")");
        return result;
    }
};

template<typename T>
struct ShowG<T, void> {
    static std::string show(T value) {
        using ShowRepr = Show<typename Generic<T>::Repr>;
        return ShowRepr::show(Generic<T>::to(value));
    };
};

template<typename T>
struct ShowU<std::vector<T>, void>
{
    static std::string show(std::vector<T> value) {
        std::string result("[");
        auto first = true;
        for (const T &x : value) {
            if (!first) {
                result.append(", ");
            }
            result.append(Show<T>::show(x));
            first = false;
        }
        result.append("]");
        return result;
    }
};

template<typename T>
std::string show(T value) {
    return Show<T>::show(value);
}

int main() {
    struct Kek {};

    const char *streetName = "Nullptr Street";
    const SimpleAddress address(streetName, 0);

    const char *aName = "Nicole Nullptr";
    const TestPerson a(aName, address, 42);
    const char *bName = "Simon Segfault";
    const TestPerson b(bName, address, 42);

    using Persons = std::vector<TestPerson>;
    const Persons persons{a, b};
    using Personss = std::vector<Persons>;
    const Personss personss { persons, persons };

    std::cout
        << show(42) << std::endl
        << show<std::string>("asd") << std::endl
//        << show<Kek>({}) << std::endl
        << show(a) << std::endl
        << show(persons) << std::endl
        << show(personss) << std::endl
        << "the end" << std::endl
        ;
}

// @TODO: Does the assemble work?

// @TODO: Try out inductive datastructures
// @TODO: Going constexpr
