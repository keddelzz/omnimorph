#include "Object.h"

#include <cstring>

#include "Value.h"

namespace json {

Object::Object()
{}

Object::Object(const json::Object &other)
{
    copy(other);
}

Object::Object(Object &&other) noexcept
{
    consume(std::move(other));
}

json::Object &Object::operator=(const Object &other)
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

json::Object &Object::operator=(Object &&other) noexcept
{
    consume(std::move(other));
    return *this;
}

void Object::insert(const String &key, const Value &value)
{
    auto storage = write(key);
    assert(storage != nullptr);
    if (storage == nullptr) return;
    *storage = value;
}

const json::Value *Object::read(const String &key) const
{
    for (uint64_t i = 0; i < size(); ++i) {
        if (m_keys[i] == key) return &m_values[i];
    }

    return nullptr;
}

json::Value *Object::write(const String &key)
{
    for (uint64_t i = 0; i < size(); ++i) {
        if (m_keys[i] == key) return &m_values[i];
    }

    auto position = this->size();
    m_keys.append(String(reinterpret_cast<char *>(key.data), key.length));
    m_values.append(json::Value());
    return &m_values[position];
}

void Object::copy(const Object &other)
{
    m_keys = other.m_keys;
    m_values = other.m_values;
}

void Object::consume(Object &&other)
{
    m_keys = std::move(other.m_keys);
    m_values = std::move(other.m_values);
}

void Object::clear()
{
    m_keys.clear();
    m_values.clear();
}

}