#pragma once

struct HNil {};

template<typename H, typename T>
struct HList
{
    constexpr explicit HList(H head, T tail)
        : head(head)
        , tail(tail)
    {}

    H head;
    T tail;
};

constexpr HNil hlist()
{
    return {};
}

template<typename H, typename ... T>
constexpr auto hlist(H head, T ... tail)
{
    return HList(head, hlist(tail ...));
}
