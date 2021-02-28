#pragma once

#include <cassert>

#include "types.h"
#include "Utils.h"

template<typename T>
struct List
{
    List()
        : List(4)
    {}
    explicit List(u64 initialCapacity)
    {
        ensureCapacity(initialCapacity);
    }

    ~List()
    {
        if (data != nullptr) {
            free(data);
            data = nullptr;
            length = 0;
            capacity = 0;
        }
    }

    constexpr bool empty() const { return length == 0; }

    constexpr const T &operator[](u64 index) const
    {
        assert(indexInBounds(index));
        return data[index];
    }
    constexpr T &operator[](u64 index)
    {
        assert(indexInBounds(index));
        return data[index];
    }

    void append(const T &value)
    {
        ensureCapacity(length + 1);
        data[length] = value;
        ++length;
    }
    void appendAll(const List<T> &other)
    {
        ensureCapacity(length + other.length);
        memcpy(&data[length], other.data, other.length);
        length += other.length;
    }

    void clear() { length = 0; }

    u64 length { 0 };
    u64 capacity { 0 };
    T   *data { nullptr };

private:
    bool indexInBounds(u64 index) const { return index < length; }

    void ensureCapacity(u64 newCapacity)
    {
        newCapacity = Utils::nextPot(newCapacity);
        if (newCapacity > capacity) {
            void *newData = nullptr;
            if (data == nullptr) {
                newData = malloc(sizeof(T) * newCapacity);
            } else {
                newData = realloc(data, sizeof(T) * newCapacity);
            }
            data = static_cast<T *>(newData);
            capacity = newCapacity;
        }
    }
};
