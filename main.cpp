#include <cstdlib>
#include <iostream>

#include "data/IterationDecision.h"

#include "cpp/FileUtils.h"
#include "cpp/Ast.h"
#include "cpp/CppParser.h"

int main()
{
    std::cout << "Hello, omnimorph!" << std::endl;

    const String filePath("../example/Vec4f.h");
    const auto fileContents = cpp::FileUtils::readEntireFile(filePath);

    using namespace cpp;
    CppParser parser;
    parser.initialize(filePath, fileContents);
    parser.foreachToplevelDeclaration([](Decl *decl) {

        return IterationDecision::Continue;
    });

    // @TODO: Pretty printer

    return EXIT_SUCCESS;
}
