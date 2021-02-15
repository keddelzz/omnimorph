#include <cstdlib>
#include <iostream>

#include "cpp/FileUtils.h"
#include "cpp/CppScanner.h"

int main()
{
    std::cout << "Hello, omnimorph!" << std::endl;

    const std::string filePath("../example/Vec3f.h");
    const auto fileContents = cpp::FileUtils::readEntireFile(filePath);
    cpp::CppScanner scanner(filePath, fileContents);
    while (scanner.hasNext()) {
        std::cout << scanner.next() << std::endl;
    }

    return EXIT_SUCCESS;
}
