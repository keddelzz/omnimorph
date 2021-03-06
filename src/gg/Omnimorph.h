#pragma once

#include "../data/StringBuilder.h"
#include "../data/String.h"
#include "../cpp/Ast.h"

namespace gg {

class Omnimorph
{
public:
    static void generateGeneric(const String &inputFile, const String &outputFile);
    static void generateGeneric(StringBuilder &buffer, const String &inputFile, const String &fileContents);

private:
    static void traverseDecls(StringBuilder &buffer, const cpp::Decl *decl);
    static void generateGeneric(StringBuilder &buffer, const cpp::Decl *decl);

    struct FieldInformation
    {
        const cpp::Decl *decl { nullptr };
        const cpp::Exp *type { nullptr };
        String name;
    };
    struct TypeInformation
    {
        const cpp::Decl *decl { nullptr };
        const cpp::TypeDecl *type { nullptr };
        String typeName;
        List<FieldInformation> fieldDecls;
    };
    static TypeInformation preprocess(const cpp::Decl *decl);

    static void makeIndentation(StringBuilder &buffer, int level);

    using EmitMemberType = void (*) (StringBuilder &buffer, const FieldInformation &field); // <type-name>
    using EmitMemberAccess = void (*) (StringBuilder &buffer, const String &instanceName, const FieldInformation &field); // <instance>.<name>

    struct Generator
    {
        TypeInformation typeInformation;
        String specializationName;

        EmitMemberType emitMemberType { nullptr };
        EmitMemberAccess emitMemberAccess { nullptr };
    };
    static void generate(Generator &generator, StringBuilder &buffer);

};

}
