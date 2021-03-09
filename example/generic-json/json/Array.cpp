#include "Array.h"

#include "Value.h"

namespace json {

Array::Array()
{}

Array::Array(const Array &other)
{
    copy(other);
}

Array::Array(Array &&other) noexcept
{
    consume(std::move(other));
}

json::Array &Array::operator=(const Array &other)
{
    if (this != &other) {
        clear();
        copy(other);
    }
    return *this;
}

json::Array &Array::operator=(Array &&other) noexcept
{
    consume(std::move(other));
    return *this;
}

void Array::copy(const Array &other)
{
    m_values = other.m_values;
}

void Array::consume(json::Array &&other)
{
    m_values = std::move(other.m_values);
}

void Array::clear()
{
    m_values.clear();
}

}