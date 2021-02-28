#include <iostream>

#include "gg/Omnimorph.h"

int main()
{
    const String inputFile("../example/Fid.h");
    StringBuilder buffer;
    gg::Omnimorph::generateGeneric(buffer, inputFile);
    std::cout << buffer.toString() << std::endl;
    return EXIT_SUCCESS;
}
