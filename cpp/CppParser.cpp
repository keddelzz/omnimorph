#include "CppParser.h"

namespace cpp {

void CppParser::initialize(std::string filePath, std::vector<u8> fileContents)
{
    this->filePath = filePath;
    scanner.initialize(std::move(filePath), std::move(fileContents));
}

void CppParser::foreachTypeDefinition(Consumer<int> consumer)
{

}

}
