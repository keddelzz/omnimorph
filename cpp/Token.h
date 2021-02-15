#pragma once

#include <ostream>

#include "types.h"
#include "TokenType.h"
#include "Lexeme.h"
#include "FileRange.h"

namespace cpp {

struct Token
{
    explicit Token() = default;
    explicit Token(TokenType type, const Lexeme &lexeme, const FileRange &range);

    TokenType type { TokenType::Error };
    Lexeme    lexeme { };
    FileRange range { };

    bool isNullToken() const;
};

std::ostream &operator<<(std::ostream &stream, const Token &token);

}
