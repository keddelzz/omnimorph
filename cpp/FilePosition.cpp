#include "FilePosition.h"

FilePosition::FilePosition(s64 line, s64 column)
    : line(line)
    , column(column)
{}

bool FilePosition::isNullPosition() const
{
    return line == -1 and
           column == -1;
}

std::ostream &operator<<(std::ostream &stream, const FilePosition &position)
{
    return stream << position.line << ':' << position.column;
}
