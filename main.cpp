#include <cstdlib>
#include <iostream>

#include "cpp/CppScanner.h"

int main()
{
    std::cout << "Hello, omnimorph!" << std::endl;

    auto scanner = CppScanner::fromString("1 + 2 * 3");
    while (scanner->hasNext()) {
        std::cout << scanner->next() << std::endl;
    }

    return EXIT_SUCCESS;
}
