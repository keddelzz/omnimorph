#pragma once

#include <cassert>
#include <cstdint>
#include <string>

#include "Array.h"
#include "Object.h"

namespace json {

class Value
{

public:
    enum class Type : uint8_t
    {
        Null,
        Undefined,

        Bool,
        Int,
        Float,

        String,

        Array,
        Object,
    };

    Value(Type type = Type::Null);
    Value(bool);
    Value(int64_t);
    Value(double);
    Value(const String &);
    Value(const json::Array &);
    Value(const json::Object &);

    Value(const json::Value &);
    Value(json::Value &&);
    json::Value &operator=(const json::Value &);
    json::Value &operator=(json::Value &&) noexcept;

    ~Value() { clear(); }

    constexpr Type type() const { return m_type; }
    constexpr bool isNull() const { return Type::Null == type(); }
    constexpr bool isUndefined() const { return Type::Undefined == type(); }

    constexpr bool isBool() const { return Type::Bool == type(); }
    constexpr bool asBool() const { assert(isBool()); return m_asBool; }

    constexpr bool isInt() const { return Type::Int == type(); }
    constexpr int64_t asInt() const { assert(isInt()); return m_asInt; }

    constexpr bool isFloat() const { return Type::Float == type(); }
    constexpr double asFloat() const { assert(isFloat()); return m_asFloat; }

    constexpr bool isNumber() const { return isInt() or isFloat(); }

    constexpr bool isString() const { return Type::String == type(); }
    constexpr const String &asString() const { assert(isString()); return m_asString; }
    constexpr String &asString() { assert(isString()); return m_asString; }

    constexpr bool isArray() const { return Type::Array == type(); }
    constexpr const json::Array &asArray() const { assert(isArray()); return m_asArray; }
    constexpr json::Array &asArray() { assert(isArray()); return m_asArray; }

    constexpr bool isObject() const { return Type::Object == type(); }
    constexpr const json::Object &asObject() const { assert(isObject()); return m_asObject; }
    constexpr json::Object &asObject() { assert(isObject()); return m_asObject; }

private:
    void copy(const json::Value &other);
    void consume(json::Value &&other);
    void clear();

private:
    Type m_type;

    union {
        bool         m_asBool;
        int64_t      m_asInt;
        double       m_asFloat;
        String       m_asString;
        json::Array  m_asArray;
        json::Object m_asObject;
    };

};

}
