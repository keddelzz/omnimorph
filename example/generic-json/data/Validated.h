#pragma once

#include <cassert>

template<typename Error, typename Value>
class Validated
{
public:
    Validated(Validated<Error, Value> &&other) noexcept
        : Validated(other.m_type)
    {
        if (other.hasValue()) {
            m_value = std::move(other.value());
        } else {
            m_error = std::move(other.error());
        }
    }

    virtual ~Validated()
    {
        if (hasValue()) {
            m_value.~Value();
        } else {
            m_error.~Error();
        }
    }

    static Validated<Error, Value> failure(Error &&error)
    {
        Validated<Error, Value> validated(Type::Failure);
        validated.m_error = std::move(error);
        return validated;
    }
    static Validated<Error, Value> success(Value &&value)
    {
        Validated<Error, Value> validated(Type::Success);
        validated.m_value = std::move(value);
        return validated;
    }

    constexpr bool hasValue() const { return Type::Success == m_type; }
    constexpr Value &&value() { assert(hasValue()); return std::move(m_value); }

    constexpr bool hasError() const { return Type::Failure == m_type; }
    constexpr Error &&error() { assert(hasError()); return std::move(m_error); }

private:
    enum class Type
    {
        Failure,
        Success
    };

    explicit Validated(Type type)
    {
        memset(this, 0, sizeof(Validated<Error, Value>));
        m_type = type;
    }

    Type m_type;
    union {
        Error m_error;
        Value m_value;
    };
};