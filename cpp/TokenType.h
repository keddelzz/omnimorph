#pragma once

#include <ostream>

#include "types.h"

enum class TokenType : u8
{
    Plus,
    Star,
    LPar,
    RPar,
    Ident,
    IntLit,

    White,
    Eof,

    Error,
    _TokenCount = Error,
};

std::ostream &operator<<(std::ostream & stream, TokenType type);
