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
        if (DeclKind::CompoundType != decl->kind) return IterationDecision::Continue;

        std::cout << "Found declaration '" << decl->name.lexeme.toString() << "'" << std::endl;
        std::cout << "    " << "It's a " << (decl->compoundType.isClass ? "class" : "struct") << "!" << std::endl;

        const auto &members = decl->compoundType.members;
        std::cout << "    " << members.length << " members:" << std::endl;

        for (auto i = 0; i < members.length; ++i) {
            auto member = members[i];
            if (DeclKind::Field != member->kind) continue;

            switch (member->visibility) {
                case MemberVisibility::Public: std::cout << "public: "; break;
                case MemberVisibility::Private: std::cout << "private: "; break;
                case MemberVisibility::Protected: std::cout << "protected: "; break;
            }
            const auto &field = member->field;
            switch (field.type->kind) {
                case ExpKind::Name: std::cout << field.type->nameExp.name.lexeme.toString(); break;
                case ExpKind::Primitive: std::cout << u8(field.type->primitiveExp.kind); break;
            }
            const auto fldName = field.name.lexeme.toString();
            std::cout << " " << fldName << std::endl;
        }

        return IterationDecision::Continue;
    });

    // @TODO: Pretty printer

    return EXIT_SUCCESS;
}
