#include "Omnimorph.h"

#include "../data/IterationDecision.h"
#include "../data/List.h"

#include "../cpp/FileUtils.h"
#include "../cpp/CppParser.h"

namespace gg {

void Omnimorph::generateGeneric(const String &inputFile, const String &outputFile)
{
    using namespace cpp;
    const auto fileContents = FileUtils::readEntireFile(inputFile);

    StringBuilder buffer;
    Omnimorph::generateGeneric(buffer, inputFile, fileContents);
    FileUtils::writeEntireFile(outputFile, buffer.toString());
}

void Omnimorph::generateGeneric(StringBuilder &buffer, const String &inputFile, const String &fileContents)
{
    using namespace cpp;

    CppParser parser;
    parser.initialize(inputFile, fileContents);

    buffer.append("#include <omnimorph/HList.h>\n");
    buffer.append("#include <omnimorph/Generic.h>\n");

    parser.foreachToplevelDeclaration([&](Decl *decl) {
        Omnimorph::traverseDecls(buffer, decl);
        return IterationDecision::Continue;
    });
}

void Omnimorph::traverseDecls(StringBuilder &buffer, const cpp::Decl *decl)
{
    using namespace cpp;

    if (DeclKind::Type != decl->kind) return;
    const auto &type = decl->type;

    if (not type.marked) return;
    Omnimorph::generateGeneric(buffer, decl);
}

void Omnimorph::generateGeneric(StringBuilder &buffer, const cpp::Decl *decl)
{
    using namespace cpp;

    Generator copyGenericGenerator {
        .typeInformation = preprocess(decl),
        .specializationName = "CopyGeneric",

        .emitMemberType = [](StringBuilder &buffer, const FieldInformation &field) {
            // @TODO: Show structure shows the structure of the type,
            //        but here we require the cpp-expression.
            Ast::showStructure(buffer, field.type);
        },
        .emitMemberAccess = [](StringBuilder &buffer, const String &instanceName, const FieldInformation &field) {
            buffer.append(instanceName);
            buffer.append('.');
            buffer.append(field.name);
        }
    };

    Omnimorph::generate(copyGenericGenerator, buffer);
}

Omnimorph::TypeInformation Omnimorph::preprocess(const cpp::Decl *decl)
{
    TypeInformation result;
    result.decl = decl;
    result.type = &decl->type;
    result.typeName = decl->name.lexeme.toString();

    for (auto i = 0; i < result.type->members.length; ++i) {
        const auto member = result.type->members[i];
        if (cpp::DeclKind::Field != member->kind) continue;

        FieldInformation field;
        field.decl = member;
        field.type = member->field.type;
        field.name = member->name.lexeme.toString();
        result.fieldDecls.append(field);
    }
    return result;
}

void Omnimorph::makeIndentation(StringBuilder &buffer, int level)
{
    const String singleIndentation("  ");
    while (level > 0) {
        buffer.append(singleIndentation);
        --level;
    }
}

void Omnimorph::generate(Generator &generator, StringBuilder &buffer)
{
    const auto &typeInformation = generator.typeInformation;
    const auto &typeName = typeInformation.typeName;
    const auto &fieldDecls = typeInformation.fieldDecls;

    buffer.append('\n');

    buffer.append("template<>\n");
    buffer.append("struct ");
    buffer.append(generator.specializationName);
    buffer.append("<");
    buffer.append(typeInformation.typeName);
    buffer.append(">\n");
    buffer.append("{\n");

    {
        const auto emitReprPrefix = [&]() {
            buffer.append(typeName);
            buffer.append("_Repr");
        };
        const auto emitReprPrefixWithSubscript = [&](u64 subscript) {
            emitReprPrefix();
            buffer.append('_');
            buffer.append(subscript);
        };
        const auto emitValueNameWithSubscript = [&](u64 subscript) {
            buffer.append("list");
            buffer.append('_');
            buffer.append(subscript);
        };

        {
            makeIndentation(buffer, 1);
            buffer.append("using ");
            emitReprPrefixWithSubscript(fieldDecls.length);
            buffer.append(" = HNil;\n");
        }

        for (auto i = fieldDecls.length - 1; i >= 0; --i) {
            const auto &field = fieldDecls[i];

            makeIndentation(buffer, 1);
            buffer.append("using ");
            emitReprPrefixWithSubscript(i);
            buffer.append(" = HList<");
            generator.emitMemberType(buffer, field);
            buffer.append(", ");
            emitReprPrefixWithSubscript(i + 1);
            buffer.append(">;\n");

            if (i == 0) break;
        }

        {
            makeIndentation(buffer, 1);
            buffer.append("using ");
            emitReprPrefix();
            buffer.append("   = ");
            emitReprPrefixWithSubscript(0);
            buffer.append(";\n");
        }

        buffer.append('\n');

        makeIndentation(buffer, 1);
        buffer.append("using Type = ");
        buffer.append(typeName);
        buffer.append(";\n");
        
        makeIndentation(buffer, 1);
        buffer.append("using Repr = "); emitReprPrefix(); buffer.append(";\n");

        buffer.append('\n');

        {
            makeIndentation(buffer, 1);
            buffer.append("static Repr to(const Type &value)\n");
            makeIndentation(buffer, 1);
            buffer.append("{\n");

            {
                {
                    makeIndentation(buffer, 2);
                    buffer.append("const ");
                    emitReprPrefixWithSubscript(fieldDecls.length);
                    buffer.append(' ');
                    emitValueNameWithSubscript(fieldDecls.length);
                    buffer.append("{};\n");
                }

                for (auto i = fieldDecls.length - 1; i >= 0; --i) {
                    const auto &field = fieldDecls[i];

                    makeIndentation(buffer, 2);
                    buffer.append("const ");
                    emitReprPrefixWithSubscript(i);
                    buffer.append(' ');
                    emitValueNameWithSubscript(i);
                    buffer.append('(');
                    generator.emitMemberAccess(buffer, "value", field);
                    buffer.append(", ");
                    emitValueNameWithSubscript(i + 1);
                    buffer.append(");\n");

                    if (i == 0) break;
                }

                {
                    makeIndentation(buffer, 2);
                    buffer.append("const ");
                    emitReprPrefix();
                    buffer.append(" &list = ");
                    emitValueNameWithSubscript(0);
                    buffer.append(";\n");
                }

                makeIndentation(buffer, 2);
                buffer.append("return list;\n");
            }

            makeIndentation(buffer, 1);
            buffer.append("}\n");

            buffer.append('\n');
        }

        {
            makeIndentation(buffer, 1);
            buffer.append("static Type from(const Repr &repr)\n");
            makeIndentation(buffer, 1);
            buffer.append("{\n");

            {
                {
                    makeIndentation(buffer, 2);
                    buffer.append("const ");
                    emitReprPrefix();
                    buffer.append(" &list = repr;\n");
                }

                for (auto i = 0; i < fieldDecls.length; ++i) {
                    makeIndentation(buffer, 2);
                    buffer.append("const ");
                    emitReprPrefixWithSubscript(i);
                    buffer.append(" &");
                    emitValueNameWithSubscript(i);
                    buffer.append(" = ");

                    if (i == 0) {
                        buffer.append("list;\n");
                    } else {
                        emitValueNameWithSubscript(i - 1);
                        buffer.append(".tail;\n");
                    }
                }

                buffer.append('\n');

                makeIndentation(buffer, 2);

                // @TODO: It would be nice if you can configure how a value of your type is
                //        instantiated (default constructor + member assignments, constructor
                //        containing all members, initializer list, struct initializer syntax)

                buffer.append("Type result;\n");

                for (auto i = 0; i < fieldDecls.length; ++i) {
                    const auto &field = fieldDecls[i];
                    makeIndentation(buffer, 2);
                    generator.emitMemberAccess(buffer, "result", field);
                    buffer.append(" = ");
                    emitValueNameWithSubscript(i);
                    buffer.append(".head;\n");
                }

                makeIndentation(buffer, 2);
                buffer.append("return result;\n");
            }

            makeIndentation(buffer, 1);
            buffer.append("}\n");
        }
    }

    buffer.append("};\n");
}

}
