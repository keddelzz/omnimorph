#pragma once

#include <cstdint>
#include <ostream>

enum class TokenType : uint8_t
{
    Plus,
    Star,
    Lpar,
    Rpar,
    Ident,
    Intlt,
    White,
    Eof,
    Error,
    _TokenCount = Error,
};

std::ostream &operator<<(std::ostream &stream, TokenType type);
