#include "Lexeme.h"

namespace cpp {

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

String Lexeme::toString() const
{
    String result;
    result.owned = false;
    result.length = end - start;
    result.data = const_cast<u8 *>(start);
    return result;
}

std::ostream &operator<<(std::ostream &stream, const Lexeme &lexeme)
{
    return stream << lexeme.toString();
}

}
