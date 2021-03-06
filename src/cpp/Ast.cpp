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
        case Visibility::Invalid  : buffer.append("INVALID"); break;
        case Visibility::Private  : buffer.append("private"); break;
        case Visibility::Protected: buffer.append("protected"); break;
        case Visibility::Public   : buffer.append("public"); break;
    }
}

void Ast::showStructure(StringBuilder &buffer, TypeKind kind) {
    switch (kind) {
        case TypeKind::Invalid: buffer.append("INVALID"); break;
        case TypeKind::Class  : buffer.append("class"); break;
        case TypeKind::Struct : buffer.append("struct"); break;
        case TypeKind::Enum   : buffer.append("enum"); break;
        case TypeKind::Union  : buffer.append("union"); break;
    }
}

void Ast::showStructure(StringBuilder &buffer, const Exp *decl, const PrimitiveExp &primitive, int level)
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

void Ast::showStructure(StringBuilder &buffer, const Exp *decl, const NameExp &name, int level)
{
    buffer.append(name.name.lexeme.toString());
}

void Ast::showStructure(StringBuilder &buffer, const Exp *exp, int level)
{
    switch (exp->kind) {
        case ExpKind::Primitive: Ast::showStructure(buffer, exp, exp->primitive, level); break;
        case ExpKind::Name     : Ast::showStructure(buffer, exp, exp->name, level); break;
        default                : buffer.append("Exp(INVALID)"); break;
    }
}

void Ast::showStructure(StringBuilder &buffer, const Decl *decl, const TypeDecl &type, int level)
{
    buffer.append("TypeDecl");
    if (type.marked) {
        buffer.append('*');
    }
    buffer.append("(\n");

    makeIndentation(buffer, level + 1);
    Ast::showStructure(buffer, decl->visibility); buffer.append(",\n");

    makeIndentation(buffer, level + 1);
    Ast::showStructure(buffer, type.kind); buffer.append(",\n");

    makeIndentation(buffer, level + 1);
    buffer.append(decl->name.lexeme.toString());

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

void Ast::showStructure(StringBuilder &buffer, const Decl *decl, const FieldDecl &field, int level)
{
    buffer.append("FieldDecl(");
    Ast::showStructure(buffer, decl->visibility); buffer.append(", ");
    Ast::showStructure(buffer, field.type, level); buffer.append(", ");
    buffer.append(decl->name.lexeme.toString()); buffer.append(")");
}

void Ast::showStructure(StringBuilder &buffer, const Decl *decl, const MethodDecl &method, int level)
{
    assert(false && "Ast::showStructure(MethodDecl) not implemented!");
}

void Ast::showStructure(StringBuilder &buffer, const Decl *decl, int level)
{
    switch (decl->kind) {
        case DeclKind::Type   : Ast::showStructure(buffer, decl, decl->type, level); break;
        case DeclKind::Field  : Ast::showStructure(buffer, decl, decl->field, level); break;
        case DeclKind::Method : Ast::showStructure(buffer, decl, decl->method, level); break;
        default               : buffer.append("Decl(INVALID)"); break;
    }
}

}
