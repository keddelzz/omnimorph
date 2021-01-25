#pragma once

struct HNil {};

template<typename H, typename T>
struct HList {
    constexpr HList(H head, T tail)
        : head(head)
        , tail(tail)
    {}

    H head;
    T tail;
};

constexpr HNil hlist() {
    return {};
}

template<typename H, typename ... T>
constexpr auto hlist(H head, T ... tail) {
    return HList(head, hlist(tail ...));
}

std::ostream &operator<<(std::ostream &stream, HNil) {
    return stream << "HNil";
}

template<typename H, typename T>
std::ostream &operator<<(std::ostream &stream, HList<H, T> hlist) {
    return stream << hlist.head << " :: " << hlist.tail;
}
