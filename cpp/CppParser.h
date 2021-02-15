#pragma once

#include "CppScanner.h"
#include "../types.h"

namespace cpp {

class CppParser
{

public:
    explicit CppParser() = default;
    void initialize(std::string filePath, std::vector<u8> fileContents);
    void initialize(std::vector<u8> fileContents) { initialize("<string>", std::move(fileContents)); }

    void foreachTypeDefinition(Consumer<int> consumer);

private:
    std::string filePath;
    CppScanner  scanner;

};

}
