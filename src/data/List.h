#pragma once

#include <cassert>
#include <cstring>

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

    List(const List<T> &other) { copy(other); }
    List(List<T> &&other) noexcept { consume(std::move(other)); }
    List<T> &operator=(const List<T> &other)
    {
        if (this != &other) {
            clear();
            copy(other);
        }
        return *this;
    }
    List<T> &operator=(List<T> &&other) noexcept
    {
        consume(std::move(other));
        return *this;
    }

    ~List() { clear(); }

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
    void append(T &&value)
    {
        ensureCapacity(length + 1);
        data[length] = std::move(value);
        ++length;
    }

    void clear()
    {
        if (data != nullptr) {
            free(data);
        }

        data = nullptr;
        length = 0;
        capacity = 0;
    }

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
            memset(data + capacity, 0, sizeof(T) * (newCapacity - capacity));
            capacity = newCapacity;
        }
    }

    void copy(const List<T> &other)
    {
        ensureCapacity(other.capacity);

        for (u64 i = 0; i < other.length; ++i) {
            data[length + i] = other[i];
        }
        length = other.length;
    }

    void consume(List<T> &&other)
    {
        length = other.length;
        capacity = other.capacity;
        data = std::exchange(other.data, nullptr);
    }

};
