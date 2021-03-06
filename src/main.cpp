#include <iostream>

#include "gg/Omnimorph.h"

int main(int argc, char *args[])
{
    constexpr auto expectedArgumentCount = 1 + 2;
    const String programPath(args[0]);

    if (argc != expectedArgumentCount) {
        std::cout << "Syntax:" << std::endl;
        std::cout << programPath << " <input-file> <output-file>" << std::endl;
        return EXIT_FAILURE;
    }

    const String inputFile(args[1]);
    const String outputFile(args[2]);
    gg::Omnimorph::generateGeneric(inputFile, outputFile);
    return EXIT_SUCCESS;
}
