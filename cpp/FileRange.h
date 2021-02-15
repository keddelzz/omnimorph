#pragma once

#include <string>
#include "../types.h"
#include "FilePosition.h"

namespace cpp {

struct FileRange
{
    explicit FileRange() = default;
    explicit FileRange(
        std::string fileName,
        const FilePosition &start,
        const FilePosition &end
    );

    std::string  fileName;
    FilePosition start;
    FilePosition end;

    bool isNullRange() const;
};

std::ostream &operator<<(std::ostream &stream, const FileRange &range);

}
