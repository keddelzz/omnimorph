#pragma once

#include "flatpointer.h"

class FlatFunction
{
public:
    template<typename A, typename B>
    constexpr FlatFunction(B (*f)(A))
        : function_pointer(reinterpret_cast<FlatPointer>(f))
    {}
    template<typename A, typename B>
    constexpr B operator()(A arg) const {
        auto f = reinterpret_cast<B (*)(A)>(function_pointer);
        return f(arg);
    }

private:
    FlatPointer function_pointer;
};