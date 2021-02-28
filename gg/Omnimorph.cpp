#include "Omnimorph.h"

#include "../data/IterationDecision.h"
#include "../data/List.h"

#include "../cpp/FileUtils.h"
#include "../cpp/CppParser.h"

namespace gg {

void Omnimorph::generateGeneric(StringBuilder &buffer, const String &inputFile)
{
    using namespace cpp;

    const auto fileContents = FileUtils::readEntireFile(inputFile);

    CppParser parser;
    parser.initialize(inputFile, fileContents);

    buffer.append("#include \"api/HList.h\"\n");
    buffer.append("#include \"api/Generic.h\"\n");

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
    Omnimorph::generateGeneric(buffer, decl, type);
}

void Omnimorph::makeIndentation(StringBuilder &buffer, int level)
{
    const String singleIndentation("  ");
    while (level > 0) {
        buffer.append(singleIndentation);
        --level;
    }
}

void Omnimorph::generateGeneric(StringBuilder &buffer, const cpp::Decl *decl, const cpp::TypeDecl &type)
{
    using namespace cpp;

    buffer.append('\n');

    const auto typeName = decl->name.lexeme.toString();

    List<const Decl *> fieldDecls;
    for (auto i = 0; i < type.members.length; ++i) {
        const auto member = type.members[i];
        if (DeclKind::Field != member->kind) continue;
        fieldDecls.append(member);
    }

    buffer.append("template<>\n");
    buffer.append("struct CopyGeneric<").append(typeName).append(">\n");
    buffer.append("{\n");

    {
        const auto emitReprPrefix = [&]() {
            buffer.append(typeName).append("_Repr");
        };
        const auto emitReprPrefixWithSubscript = [&](u64 subscript) {
            emitReprPrefix();
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
            const auto field = fieldDecls[i];

            makeIndentation(buffer, 1);
            buffer.append("using ");
            emitReprPrefixWithSubscript(i);
            buffer.append(" = HList<");
            Ast::showStructure(buffer, field->field.type);
                // @TODO: Show structure shows the structure of the type,
                //        but here we require the cpp-expression.
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
        buffer.append("using Type = ").append(typeName).append(";\n");
        makeIndentation(buffer, 1);
        buffer.append("using Repr = "); emitReprPrefix(); buffer.append(";\n");

        //  @TODO: static Repr to(const Type &value)
        //  @TODO: static Type from(const Repr &repr)
    }

    buffer.append("};\n");
}

}
