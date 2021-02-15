#include <cstdlib>
#include <iostream>

#include "cpp/CppScanner.h"

int main()
{
    std::cout << "Hello, omnimorph!" << std::endl;

    auto scanner = cpp::CppScanner::fromFile("../example/cpptokens.txt");
    while (scanner->hasNext()) {
        std::cout << scanner->next() << std::endl;
    }

    return EXIT_SUCCESS;
}
