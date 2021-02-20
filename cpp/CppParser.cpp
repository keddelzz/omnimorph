#include "CppParser.h"

namespace cpp {

void CppParser::initialize(const String &filePath, const String &fileContents)
{
    this->filePath = filePath;
    scanner.initialize(filePath, fileContents);
}
}

void CppParser::foreachTypeDefinition(Consumer<int> consumer)
{

}

}
