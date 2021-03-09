#pragma once

#include "types.h"

static_assert(sizeof(char) == sizeof(u8));

// @TODO: Split StringView and String
struct String
{
    explicit String(u64 length = 0);
    String(char *string, s64 length = -1);
    String(const char *string, s64 length = -1);

    String(const String &);
    String(String &&) noexcept;
    String &operator=(const String &) noexcept;
    String &operator=(String &&) noexcept;

    ~String() { clear(); }

    constexpr u8 operator[](u64 index) const { return data[index]; }
    constexpr u8 &operator[](u64 index) { return data[index]; }

    bool operator==(const String &other) const;
    bool operator!=(const String &other) const { return not (*this == other); }

    constexpr bool empty() const { return length == 0; }

    void clear();

private:
    static void initialize(String &string, const char *str, s64 length, bool own);

    void copy(const String &other);
    void consume(String &&other);

public:
    bool owned : 1 { false };
    u64 length : 63 { 0 };
    u8  *data { nullptr };
};

std::ostream &operator<<(std::ostream &stream, const String &string);
