#include <cstdlib>
#include <iostream>

#include "data/IterationDecision.h"

#include "cpp/FileUtils.h"
#include "cpp/Ast.h"
#include "cpp/CppParser.h"

#include "gg/Omnimorph.h"

int main_()
{
    std::cout << "Hello, omnimorph!" << std::endl;

    const String filePath("../example/Vec4f.h");
    const auto fileContents = cpp::FileUtils::readEntireFile(filePath);

    using namespace cpp;
    CppParser parser;
    parser.initialize(filePath, fileContents);
    parser.foreachToplevelDeclaration([](Decl *decl) {
        StringBuilder buffer;
        Ast::showStructure(buffer, decl);
        std::cout << buffer.toString() << std::endl;
        return IterationDecision::Continue;
    });

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    const String inputFile("../example/Fid.h");
    StringBuilder buffer;
    gg::Omnimorph::generateGeneric(buffer, inputFile);
    std::cout << buffer.toString() << std::endl;
    return EXIT_SUCCESS;
}
