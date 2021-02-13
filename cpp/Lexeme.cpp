#include "Lexeme.h"

Lexeme::Lexeme()
    : Lexeme(nullptr, nullptr)
{}

Lexeme::Lexeme(const u8 *start, const u8 *end)
    : start(start)
    , end(end)
{}

bool Lexeme::isNullLexeme() const
{
    return start == nullptr and
           end == nullptr;
}

std::ostream &operator<<(std::ostream &stream, const Lexeme &lexeme)
{
    // @Cleanup
    std::string string;
    const auto lexemeLength = lexeme.end - lexeme.start;
    string.resize(lexemeLength);
    memcpy(string.data(), lexeme.start, lexemeLength);
    return stream << string;
}
