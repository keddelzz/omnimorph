#include "Value.h"

#include <iostream>

namespace json {

Value::Value(Type type)
    : m_type(type)
{
    switch (m_type) {
        case Type::Null: break;
        case Type::Undefined: break;
        case Type::Bool: m_asBool = false; break;
        case Type::Int: m_asInt = 0;  break;
        case Type::Float: m_asFloat = 0;  break;
        case Type::String: m_asString = "";  break;
        case Type::Array: m_asArray = json::Array(); break;
        case Type::Object: m_asObject = json::Object(); break;
        default: assert(false); break;
    }
}

Value::Value(bool value)
    : Value(Type::Bool)
{
    m_asBool = value;
}

Value::Value(int64_t value)
    : Value(Type::Int)
{
    m_asInt = value;
}

Value::Value(double value)
    : Value(Type::Float)
{
    m_asFloat = value;
}

Value::Value(const String &value)
    : Value(Type::String)
{
    m_asString = value;
}

Value::Value(const json::Array &value)
    : Value(Type::Array)
{
    m_asArray = value;
}

Value::Value(const json::Object &value)
    : Value(Type::Object)
{
    m_asObject = value;
}

Value::Value(const json::Value &other)
    : Value(other.type())
{
    copy(other);
}

Value::Value(Value &&other)
    : Value(Type::Null)
{
    consume(std::move(other));
}

json::Value &Value::operator=(const Value &other)
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

json::Value &Value::operator=(Value &&other) noexcept
{
    consume(std::move(other));
    return *this;
}

void Value::copy(const json::Value &other)
{
    m_type = other.type();

    switch (type()) {
        case Type::Null: break;
        case Type::Undefined: break;
        case Type::Bool: m_asBool = other.asBool(); break;
        case Type::Int: m_asInt = other.asInt(); break;
        case Type::Float: m_asFloat = other.asFloat(); break;
        case Type::String: m_asString = other.asString(); break;
        case Type::Array: m_asArray = other.asArray(); break;
        case Type::Object: m_asObject = other.asObject(); break;
        default: assert(false); break;
    }
}

void Value::consume(Value &&other)
{
    m_type = other.type();

    switch (type()) {
        case Type::Null: break;
        case Type::Undefined: break;
        case Type::Bool: m_asBool = other.asBool(); break;
        case Type::Int: m_asInt = other.asInt(); break;
        case Type::Float: m_asFloat = other.asFloat(); break;
        case Type::String: m_asString = std::move(other.asString()); break;
        case Type::Array: m_asArray = std::move(other.asArray()); break;
        case Type::Object: m_asObject = std::move(other.asObject()); break;
        default: assert(false); break;
    }
}

void Value::clear()
{
    switch (type()) {
        case Type::Null:
        case Type::Undefined:
        case Type::Bool:
        case Type::Int:
        case Type::Float:
            m_asInt = 0;
            break;
        case Type::String:
            m_asString.clear();
            break;
        case Type::Array:
            m_asArray.clear();
            break;
        case Type::Object:
            m_asObject.clear();
            break;
        default:
            assert(false);
            break;
    }
}

}
