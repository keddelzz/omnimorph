#include "TokenType.h"

#include <cassert>

std::ostream &operator<<(std::ostream &stream, TokenType type)
{
    switch (type) {
        case TokenType::Plus: return stream << "Plus";
        case TokenType::Star: return stream << "Star";
        case TokenType::Lpar: return stream << "Lpar";
        case TokenType::Rpar: return stream << "Rpar";
        case TokenType::Ident: return stream << "Ident";
        case TokenType::Intlt: return stream << "Intlt";
        case TokenType::White: return stream << "White";
        case TokenType::Eof: return stream << "Eof";
        case TokenType::Error: return stream << "Error";
        default: assert(false);
    }
    return stream;
}
