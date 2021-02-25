#pragma once

#include "types.h"

static_assert(sizeof(char) == sizeof(u8));

struct String
{
    explicit String(u64 length = 0);
    String(char *string, s64 length = -1);
    String(const char *string, s64 length = -1);
    String(const String &other);
    ~String();

    constexpr u8 operator[](u64 index) const { return data[index]; }
    constexpr u8 &operator[](u64 index) { return data[index]; }
    
    constexpr bool empty() const { return length == 0; }

    bool owned : 1 { false };
    u64 length : 63 { 0 };
    u8  *data { nullptr };

    static void initialize(String &string, const char *str, s64 length, bool own);
};

std::ostream &operator<<(std::ostream &stream, const String &string);
