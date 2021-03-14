#include "Omnimorph.h"

#include "../data/IterationDecision.h"
#include "../data/List.h"

#include "../cpp/FileUtils.h"
#include "../cpp/CppParser.h"

namespace gg {

// @TODO: Think of a way to configure how members are accessed
//        (direct, getter and setter)

// @TODO: It would be nice if you can configure how a value of your type is
//        instantiated (default constructor + member assignments, constructor
//        containing all members, initializer list, struct initializer syntax)

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

    buffer.append("#pragma once\n");
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

void showType(StringBuilder &buffer, const cpp::Exp *type)
{
    // @TODO: Show structure shows the structure of the type,
    //        but here we require the cpp-expression.
    cpp::Ast::showStructure(buffer, type);
}

void Omnimorph::generateGeneric(StringBuilder &buffer, const cpp::Decl *decl)
{
    using namespace cpp;

    const auto typeInformation = preprocess(decl);

    Generator copyGenericGenerator {
        .typeInformation = &typeInformation,
        .specializationNamePrefix = "Copy",

        .generation = Generation(u8(Generation::To) | u8(Generation::From)),
        .constParameter = Generation(u8(Generation::To) | u8(Generation::From)),

        .emitMemberType = [](StringBuilder &buffer, const FieldInformation &field) {
            showType(buffer, field.type);
        },
        .emitMemberAccess = [](StringBuilder &buffer, const String &instanceName, const FieldInformation &field, AccessMode mode) {
            (void) mode;
            buffer.append(instanceName);
            buffer.append('.');
            buffer.append(field.name);
        }
    };
    Omnimorph::generateUnlabelledAndLabelled(copyGenericGenerator, buffer);

    {
        Generator referenceGenericGenerator {
            .typeInformation = &typeInformation,
            .specializationNamePrefix = "Reference",

            .generation = Generation::To,
            .constParameter = Generation::None,

            .emitMemberType = [](StringBuilder &buffer, const FieldInformation &field) {
                showType(buffer, field.type);
                buffer.append(" &");
            },
            .emitMemberAccess = [](StringBuilder &buffer, const String &instanceName, const FieldInformation &field, AccessMode mode) {
                (void) mode;
                buffer.append(instanceName);
                buffer.append('.');
                buffer.append(field.name);
            }
        };
        Omnimorph::generateUnlabelledAndLabelled(referenceGenericGenerator, buffer);

        Generator constReferenceGenericGenerator {
            .typeInformation = &typeInformation,
            .specializationNamePrefix = "ConstReference",

            .generation = Generation::To,
            .constParameter = Generation::To,

            .emitMemberType = [](StringBuilder &buffer, const FieldInformation &field) {
                buffer.append("const ");
                showType(buffer, field.type);
                buffer.append(" &");
            },
            .emitMemberAccess = [](StringBuilder &buffer, const String &instanceName, const FieldInformation &field, AccessMode mode) {
                (void) mode;
                buffer.append(instanceName);
                buffer.append('.');
                buffer.append(field.name);
            }
        };
        Omnimorph::generateUnlabelledAndLabelled(constReferenceGenericGenerator, buffer);
    }

    {
        Generator pointerGenericGenerator {
            .typeInformation = &typeInformation,
            .specializationNamePrefix = "Pointer",

            .generation = Generation::To,
            .constParameter = Generation::None,

            .emitMemberType = [](StringBuilder &buffer, const FieldInformation &field) {
                showType(buffer, field.type);
                buffer.append(" *");
            },
            .emitMemberAccess = [](StringBuilder &buffer, const String &instanceName, const FieldInformation &field, AccessMode mode) {
                (void) mode;
                buffer.append('&');
                buffer.append(instanceName);
                buffer.append('.');
                buffer.append(field.name);
            }
        };
        Omnimorph::generateUnlabelledAndLabelled(pointerGenericGenerator, buffer);

        Generator constPointerGenericGenerator {
            .typeInformation = &typeInformation,
            .specializationNamePrefix = "ConstPointer",

            .generation = Generation::To,
            .constParameter = Generation::To,

            .emitMemberType = [](StringBuilder &buffer, const FieldInformation &field) {
                buffer.append("const ");
                showType(buffer, field.type);
                buffer.append(" *");
            },
            .emitMemberAccess = [](StringBuilder &buffer, const String &instanceName, const FieldInformation &field, AccessMode mode) {
                (void) mode;
                buffer.append('&');
                buffer.append(instanceName);
                buffer.append('.');
                buffer.append(field.name);
            }
        };
        Omnimorph::generateUnlabelledAndLabelled(constPointerGenericGenerator, buffer);
    }
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

void Omnimorph::generateUnlabelledAndLabelled(Generator &generator, StringBuilder &buffer)
{
    generator.labelled = false;
    Omnimorph::generate(generator, buffer);

    generator.labelled = true;
    Omnimorph::generate(generator, buffer);
}

void Omnimorph::generate(Generator &generator, StringBuilder &buffer)
{
    const auto generateTo   = bool(u8(Generation::To) & u8(generator.generation));
    const auto generateFrom = bool(u8(Generation::From) & u8(generator.generation));

    if (not generateFrom and not generateTo)
        return;

    const auto constArgumentTo   = bool(u8(Generation::To) & u8(generator.constParameter));
    const auto constArgumentFrom = bool(u8(Generation::From) & u8(generator.constParameter));

    const auto &typeInformation = *generator.typeInformation;
    const auto &typeName = typeInformation.typeName;
    const auto &fieldDecls = typeInformation.fieldDecls;

    buffer.append('\n');

    buffer.append("template<>\n");
    buffer.append("struct ");

    buffer.append(generator.specializationNamePrefix);
    if (generator.labelled) {
        buffer.append("Labelled");
    }
    buffer.append("Generic");

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
            if (generator.labelled) {
                buffer.append("Named<");
            }
            generator.emitMemberType(buffer, field);
            if (generator.labelled) {
                buffer.append(">");
            }
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

        if (generator.labelled) {
            makeIndentation(buffer, 1);
            buffer.append("constexpr static auto name = \"");
            buffer.append(typeName);
            buffer.append("\";\n");
        }

        buffer.append('\n');

        if (generateTo) {
            makeIndentation(buffer, 1);
            buffer.append("static Repr to(");
            if (constArgumentTo) {
                buffer.append("const ");
            }
            buffer.append("Type &value)\n");

            makeIndentation(buffer, 1);
            buffer.append("{\n");

            {
                {
                    makeIndentation(buffer, 2);
                    if (constArgumentTo) {
                        buffer.append("const ");
                    }
                    emitReprPrefixWithSubscript(fieldDecls.length);
                    buffer.append(' ');
                    emitValueNameWithSubscript(fieldDecls.length);
                    buffer.append("{};\n");
                }

                for (auto i = fieldDecls.length - 1; i >= 0; --i) {
                    const auto &field = fieldDecls[i];

                    makeIndentation(buffer, 2);
                    if (constArgumentTo) {
                        buffer.append("const ");
                    }
                    emitReprPrefixWithSubscript(i);
                    buffer.append(' ');
                    emitValueNameWithSubscript(i);
                    buffer.append('(');

                    if (generator.labelled) {
                        buffer.append("Named<");
                        generator.emitMemberType(buffer, field);
                        buffer.append(">(\"");
                        buffer.append(field.name);
                        buffer.append("\", ");
                    }
                    generator.emitMemberAccess(buffer, "value", field, AccessMode::Read);
                    if (generator.labelled) {
                        buffer.append(')');
                    }
                    buffer.append(", ");
                    emitValueNameWithSubscript(i + 1);
                    buffer.append(");\n");

                    if (i == 0) break;
                }

                {
                    makeIndentation(buffer, 2);
                    if (constArgumentTo) {
                        buffer.append("const ");
                    }
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
        }

        if (generateTo and generateFrom) {
            buffer.append('\n');
        }

        if (generateFrom) {
            makeIndentation(buffer, 1);
            buffer.append("static Type from(");
            if (constArgumentFrom) {
                buffer.append("const ");
            }
            buffer.append("Repr &repr)\n");

            makeIndentation(buffer, 1);
            buffer.append("{\n");

            {
                {
                    makeIndentation(buffer, 2);
                    if (constArgumentFrom) {
                        buffer.append("const ");
                    }
                    emitReprPrefix();
                    buffer.append(" &list = repr;\n");
                }

                for (auto i = 0; i < fieldDecls.length; ++i) {
                    makeIndentation(buffer, 2);
                    if (constArgumentFrom) {
                        buffer.append("const ");
                    }
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
                buffer.append("Type result;\n");

                for (auto i = 0; i < fieldDecls.length; ++i) {
                    const auto &field = fieldDecls[i];
                    makeIndentation(buffer, 2);
                    generator.emitMemberAccess(buffer, "result", field, AccessMode::Write);
                    buffer.append(" = ");
                    emitValueNameWithSubscript(i);
                    buffer.append(".head");
                    if (generator.labelled) {
                        buffer.append(".value");
                    }
                    buffer.append(";\n");
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
