#pragma once

#include <ostream>

#include "../data/types.h"
#include "../data/String.h"

namespace cpp {

struct Lexeme
{
    explicit Lexeme();
    explicit Lexeme(const u8 *start, const u8 *end);

    const u8 *start; // inclusive
    const u8 *end;   // exclusive

    bool isNullLexeme() const;
    String toString() const;
};

std::ostream &operator<<(std::ostream &, const Lexeme &lexeme);

}
