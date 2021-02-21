#include <cstdlib>
#include <iostream>

#include "cpp/FileUtils.h"
#include "cpp/CppParser.h"

int main()
{
    std::cout << "Hello, omnimorph!" << std::endl;

    const String filePath("../example/Vec4f.h");
    const auto fileContents = cpp::FileUtils::readEntireFile(filePath);

    cpp::CppParser parser;
    parser.initialize(filePath, fileContents);
    parser.foreachTypeDefinition([](auto) {
    });

    return EXIT_SUCCESS;
}
