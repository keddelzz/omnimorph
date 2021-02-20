#include "FileRange.h"

namespace cpp {

FileRange::FileRange(
    const String &fileName,
    const FilePosition &start,
    const FilePosition &end)
    : fileName(fileName)
    , start(start)
    , end(end)
{}

bool FileRange::isNullRange() const
{
    return fileName.empty() and
           start.isNullPosition() and
           end.isNullPosition();
}

std::ostream &operator<<(std::ostream &stream, const FileRange &range)
{
    return stream
        << range.fileName << ':'
        << range.start << ", "
        << range.fileName << ':'
        << range.end;
}

}
