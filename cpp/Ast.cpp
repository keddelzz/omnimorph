#include "Ast.h"

namespace cpp {

void Ast::makeIndentation(StringBuilder &buffer, int level)
{
    while (level > 0) {
        buffer.append("  ");
        --level;
    }
}

void Ast::showStructure(StringBuilder &buffer, Visibility visibility)
{
    switch (visibility) {
        case Visibility::Invalid  : buffer.append("Invalid"); break;
        case Visibility::Private  : buffer.append("Private"); break;
        case Visibility::Protected: buffer.append("Protected"); break;
        case Visibility::Public   : buffer.append("Public"); break;
    }
}

void Ast::showStructure(StringBuilder &buffer, TypeKind kind) {
    switch (kind) {
        case TypeKind::Invalid: buffer.append("Invalid"); break;
        case TypeKind::Class  : buffer.append("Class"); break;
        case TypeKind::Struct : buffer.append("Struct"); break;
        case TypeKind::Enum   : buffer.append("Enum"); break;
        case TypeKind::Union  : buffer.append("Union"); break;
    }
}

void Ast::showStructure(StringBuilder &buffer, Exp *decl, PrimitiveExp &primitive, int level)
{
    switch (primitive.kind) {
        case PrimitiveExpKind::Invalid : buffer.append("INVALID"); break;
        case PrimitiveExpKind::Bool    : buffer.append("bool"); break;
        case PrimitiveExpKind::Char    : buffer.append("char"); break;
        case PrimitiveExpKind::Double  : buffer.append("double"); break;
        case PrimitiveExpKind::Float   : buffer.append("float"); break;
        case PrimitiveExpKind::Int     : buffer.append("int"); break;
        case PrimitiveExpKind::Long    : buffer.append("long"); break;
        case PrimitiveExpKind::Short   : buffer.append("short"); break;
        case PrimitiveExpKind::Void    : buffer.append("void"); break;
        case PrimitiveExpKind::Wchar_t : buffer.append("wchar_t"); break;
    }
}

void Ast::showStructure(StringBuilder &buffer, Exp *decl, NameExp &name, int level)
{
    buffer.append(name.name.lexeme.toString());
}

void Ast::showStructure(StringBuilder &buffer, Exp *exp, int level)
{
    switch (exp->kind) {
        case ExpKind::Primitive: Ast::showStructure(buffer, exp, exp->primitive, level); break;
        case ExpKind::Name     : Ast::showStructure(buffer, exp, exp->name, level); break;
        default                : buffer.append("Exp(Invalid)"); break;
    }
}

void Ast::showStructure(StringBuilder &buffer, Decl *decl, TypeDecl &type, int level)
{
    buffer.append("TypeDecl(\n");

    makeIndentation(buffer, level + 1);
    Ast::showStructure(buffer, decl->visibility); buffer.append(",\n");

    makeIndentation(buffer, level + 1);
    Ast::showStructure(buffer, type.kind);

    if (not type.members.empty()) {
        buffer.append(",\n");

        for (auto i = 0; i < type.members.length; ++i) {
            makeIndentation(buffer, level + 1);
            Ast::showStructure(buffer, type.members[i], level + 1);

            const bool atEnd = i == type.members.length - 1;
            if (not atEnd) buffer.append(",\n");
        }
    }
    buffer.append("\n");

    makeIndentation(buffer, level);
    buffer.append(")");
}

void Ast::showStructure(StringBuilder &buffer, Decl *decl, FieldDecl &field, int level)
{
    buffer.append("FieldDecl(\n");

    makeIndentation(buffer, level + 1);
    Ast::showStructure(buffer, decl->visibility); buffer.append(",\n");

    makeIndentation(buffer, level + 1);
    Ast::showStructure(buffer, field.type, level); buffer.append(",\n");

    makeIndentation(buffer, level + 1);
    buffer.append(field.name.lexeme.toString()); buffer.append("\n");

    makeIndentation(buffer, level);
    buffer.append(")");
}

void Ast::showStructure(StringBuilder &buffer, Decl *decl, MethodDecl &method, int level)
{
    assert(false && "Ast::showStructure(MethodDecl) not implemented!");
}

void Ast::showStructure(StringBuilder &buffer, Decl *decl, int level)
{
    switch (decl->kind) {
        case DeclKind::Type   : Ast::showStructure(buffer, decl, decl->type, level); break;
        case DeclKind::Field  : Ast::showStructure(buffer, decl, decl->field, level); break;
        case DeclKind::Method : Ast::showStructure(buffer, decl, decl->method, level); break;
        default               : buffer.append("Decl(Invalid)"); break;
    }
}

}
