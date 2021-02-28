#pragma once

#include "../data/types.h"
#include "../data/String.h"
#include "FilePosition.h"

namespace cpp {

struct FileRange
{
    explicit FileRange() = default;
    explicit FileRange(
        const String &fileName,
        const FilePosition &start,
        const FilePosition &end
    );

    String       fileName;
    FilePosition start;
    FilePosition end;

    bool isNullRange() const;
};

std::ostream &operator<<(std::ostream &stream, const FileRange &range);

}
