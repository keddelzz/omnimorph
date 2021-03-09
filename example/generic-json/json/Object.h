#pragma once

#include <cstdint>

#include "../data/types.h"

namespace json {

class Value;

class Object
{
public:
    Object();

    Object(const json::Object &);
    Object(json::Object &&) noexcept;
    json::Object &operator=(const json::Object &);
    json::Object &operator=(json::Object &&) noexcept;

    ~Object() { clear(); }

    void insert(const String &key, const json::Value &value);
    constexpr uint64_t size() const { return m_keys.length; }
    constexpr bool isEmpty() const { return size() == 0; }
    bool contains(const String &key) const { return read(key) != nullptr; }
    constexpr const String &key(uint64_t index) const { return m_keys[index]; }
    const json::Value &operator[](const String &key) const { assert(contains(key)); return *read(key); }

    void clear();

private:
    const json::Value *read(const String &key) const;
    json::Value *write(const String &key);

    void copy(const json::Object &other);
    void consume(json::Object &&other);

private:
    List<String> m_keys;
    List<json::Value> m_values;
};

}
