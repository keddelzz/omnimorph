#pragma once

#include "../data/StringBuilder.h"
#include "../data/String.h"
#include "../cpp/Ast.h"

namespace gg {

class Omnimorph
{
public:
    static void generateGeneric(StringBuilder &buffer, const String &inputFile);

private:
    static void traverseDecls(StringBuilder &buffer, const cpp::Decl *decl);

    static void makeIndentation(StringBuilder &buffer, int level);
    static void generateGeneric(StringBuilder &buffer, const cpp::Decl *decl, const cpp::TypeDecl &type);
};

}
