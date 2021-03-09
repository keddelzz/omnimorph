#pragma once

#include <cstdint>

#include "../data/types.h"

namespace json {

class Value;

class Array
{
public:
    Array();

    Array(const json::Array &);
    Array(json::Array &&) noexcept;
    json::Array &operator=(const json::Array &);
    json::Array &operator=(json::Array &&) noexcept;

    ~Array() { clear(); }

    void append(const json::Value &value) { m_values.append(value); }
    constexpr uint64_t size() const { return m_values.length; }
    constexpr bool isEmpty() const { return size() == 0; }
    const json::Value &operator[](uint64_t index) const { return m_values[index]; }

    void clear();

private:
    void copy(const json::Array &other);
    void consume(json::Array &&other);

private:
    List<json::Value> m_values;
};

}
