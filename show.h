#pragma once

#include <string>

template<typename T>
struct ShowS {
    constexpr ShowS() = default;
    virtual std::string show(T) = 0;
};

template<>
struct ShowS<int> {
    constexpr ShowS() = default;
    std::string show(int value) {
        return std::to_string(value);
    }
};

template<>
struct ShowS<const char *> {
    constexpr ShowS() = default;
    std::string show(const char *value) {
        return std::string(value);
    }
};



// https://stackoverflow.com/questions/257288/templated-check-for-the-existence-of-a-class-member-function

template<typename T>
struct ShowG
{
    constexpr ShowG() = default;
    std::string show(T) { return "<generic>"; }
};

template<typename T, ShowS<T>>
struct ShowG
{
    constexpr ShowG() = default;
    std::string show(T value) {
        return ShowS<T>().show(value);
    }
};

template<>
struct ShowG<HNil>
{
    constexpr ShowG() = default;
    std::string show(HNil) {
        return "HNil";
    }
};

template<typename H, typename T>
struct ShowS<HList<H, T>>
{
    constexpr ShowS() = default;
    std::string show(HList<H, T> value) {
        ShowG<H> h;
        ShowG<T> t;
        return h.show(value.head) + " :: " + t.show(value.tail);
    }
};
