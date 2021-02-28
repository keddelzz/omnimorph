#pragma once

#include <cstdint>
#include <ostream>

namespace cpp {

enum class TokenType : int16_t
{
    Error = -1,
    Sym_PlusPlus,
    Sym_MinusMinus,
    Sym_PlusEqual,
    Sym_Plus,
    Sym_MinusEqual,
    Sym_Minus,
    Sym_StarEqual,
    Sym_Star,
    Sym_SlashEqual,
    Sym_Slash,
    Sym_PercentEqual,
    Sym_Percent,
    Sym_LtLtEqual,
    Sym_LtLt,
    Sym_Le,
    Sym_Lt,
    Sym_GtGtEqual,
    Sym_GtGt,
    Sym_Ge,
    Sym_Gt,
    Sym_EqualEqual,
    Sym_Equal,
    Sym_BangEqual,
    Sym_Bang,
    Sym_AmpAmp,
    Sym_AmpEqual,
    Sym_Amp,
    Sym_BarBar,
    Sym_BarEqual,
    Sym_Bar,
    Sym_Tilde,
    Sym_CircumflexEqual,
    Sym_Circumflex,
    Sym_QMark,
    Sym_ColonColon,
    Sym_Colon,
    Sym_Semicolon,
    Sym_Comma,
    Sym_Hash,
    Sym_DotDotDot,
    Sym_Dot,
    Sym_OpenParen,
    Sym_CloseParen,
    Sym_OpenBracket,
    Sym_CloseBracket,
    Sym_OpenCurly,
    Sym_CloseCurly,
    Kw_and,
    Kw_and_eq,
    Kw_asm,
    Kw_auto,
    Kw_bitor,
    Kw_bitand,
    Kw_bool,
    Kw_break,
    Kw_case,
    Kw_catch,
    Kw_char,
    Kw_class,
    Kw_compl,
    Kw_const,
    Kw_const_cast,
    Kw_continue,
    Kw_default,
    Kw_delete,
    Kw_do,
    Kw_double,
    Kw_dynamic_cast,
    Kw_else,
    Kw_enum,
    Kw_explicit,
    Kw_export,
    Kw_extern,
    Kw_false,
    Kw_float,
    Kw_for,
    Kw_friend,
    Kw_goto,
    Kw_if,
    Kw_inline,
    Kw_int,
    Kw_long,
    Kw_mutable,
    Kw_namespace,
    Kw_new,
    Kw_not,
    Kw_not_eq,
    Kw_symbol,
    Kw_or,
    Kw_or_eq,
    Kw_private,
    Kw_protected,
    Kw_public,
    Kw_register,
    Kw_reinterpret_cast,
    Kw_return,
    Kw_short,
    Kw_signed,
    Kw_sizeof,
    Kw_static,
    Kw_static_cast,
    Kw_struct,
    Kw_switch,
    Kw_template,
    Kw_this,
    Kw_throw,
    Kw_true,
    Kw_try,
    Kw_typedef,
    Kw_typeid,
    Kw_typename,
    Kw_union,
    Kw_unsigned,
    Kw_using,
    Kw_virtual,
    Kw_void,
    Kw_volatile,
    Kw_wchar_t,
    Kw_while,
    Kw_xor,
    Kw_xor_eq,
    HexIntLit,
    OctIntLit,
    DecIntLit,
    FloatLit,
    CharLit,
    StringLit,
    Ident,
    White,
    Comment_SingleLine,
    Comment_MultiLine,
    Eof,
    _TokenCount,
};

std::ostream &operator<<(std::ostream &stream, TokenType type);

}
