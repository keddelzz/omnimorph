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

    enum class Generation : u8
    {
        None = 0x0,
        To   = 0x1,
        From = 0x2
    };

    enum class AccessMode : u8
    {
        Read,
        Write
    };

    using EmitMemberType = void (*) (StringBuilder &buffer, const FieldInformation &field); // <type-name>
    using EmitMemberAccess = void (*) (StringBuilder &buffer, const String &instanceName, const FieldInformation &field, AccessMode mode); // <instance>.<name>

    struct Generator
    {
        const TypeInformation *typeInformation { nullptr };
        String specializationNamePrefix;

        Generation generation { Generation::None };
        Generation constParameter { Generation::None };
        bool labelled { false };
        EmitMemberType emitMemberType { nullptr };
        EmitMemberAccess emitMemberAccess { nullptr };
    };
    static void generate(Generator &generator, StringBuilder &buffer);

};

}
