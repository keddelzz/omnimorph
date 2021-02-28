#pragma once

#include "types.h"

class Utils
{
public:
    constexpr static u64 nextPot(u64 value)
    {
        --value;
        value |= value >> (1 << 0);
        value |= value >> (1 << 1);
        value |= value >> (1 << 2);
        value |= value >> (1 << 3);
        value |= value >> (1 << 4);
        value |= value >> (1 << 5);
        ++value;
        return value;
    }

private:
    Utils() = delete;
};
