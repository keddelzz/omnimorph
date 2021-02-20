#pragma once

#include "../data/types.h"

#include "CppScanner.h"

namespace cpp {

class CppParser
{

public:
    explicit CppParser() = default;
    void initialize(const String &filePath, const String &fileContents);

    void foreachTypeDefinition(Consumer<int> consumer);

private:
    String     filePath;
    CppScanner scanner;

};

}
