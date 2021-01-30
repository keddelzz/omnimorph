#pragma once

#include "flatpointer.h"

template<typename A, typename B>
class FlatFunction
{
public:
    constexpr FlatFunction(B (*f)(A))
        : function_pointer(reinterpret_cast<FlatPointer>(f))
    {}
    constexpr B operator()(A arg) const {
        auto f = reinterpret_cast<B (*)(A)>(function_pointer);
        return f(arg);
    }

private:
    FlatPointer function_pointer;
};