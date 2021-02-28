#pragma once

#include "types.h"
#include "String.h"

class StringBuilder
{
public:
    explicit StringBuilder();

    StringBuilder &append(u8 c);
    StringBuilder &append(const String &string);

    bool empty() const { return length == 0; }
    String toString();

private:
    void ensureCapacity(u64 newCapacity);

    u64 length  { 0 };
    u64 capacity { 0 };
    u8 *data { nullptr };
};
