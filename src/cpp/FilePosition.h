#pragma once

#include <ostream>

#include "../data/types.h"

namespace cpp {

struct FilePosition
{
    explicit FilePosition() = default;
    explicit FilePosition(s64 line, s64 column);

    s64 line { -1 };
    s64 column { -1 };

    bool isNullPosition() const;
};

std::ostream &operator<<(std::ostream &stream, const FilePosition &position);

}
