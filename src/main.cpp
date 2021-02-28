#include <iostream>

#include "gg/Omnimorph.h"

int main()
{
    const String inputFile("../../example/Fid.h");
    const String outputFile("../../example/Fid.h.generic");
    gg::Omnimorph::generateGeneric(inputFile, outputFile);
    return EXIT_SUCCESS;
}
