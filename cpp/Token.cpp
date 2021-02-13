#include "Token.h"

Token::Token(
    TokenType type,
    const Lexeme &lexeme,
    const FileRange &range)
    : type(type)
    , lexeme(lexeme)
    , range(range)
{}

bool Token::isNullToken() const
{
    return TokenType::Error == type and
           lexeme.isNullLexeme() and
           range.isNullRange();
}

std::ostream &operator<<(std::ostream &stream, const Token &token)
{
    return stream
        << "Token("
        << token.type   << ", "
        << token.lexeme << ", "
        << token.range
        << ")";
}
