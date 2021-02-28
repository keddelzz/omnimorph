#pragma once

#include <cassert>

#include "../data/types.h"

namespace cpp {

template<typename Iterable, typename Elem, u64 size>
class Lookahead
{
public:
    static_assert(size > 0, "Lookahead.size has to be positive!");
    Lookahead()
        : m_read(0)
        , m_write(0)
    {}
    ~Lookahead() = default;

    constexpr Iterable &underlying() { return m_underlying; }

    bool canPeek(u16 offset = 0)
    {
        return requireLookahead(offset + 1);
    }
    const Elem &peek(u16 offset = 0)
    {
        assert(canPeek(offset));
        return m_lookahead[wrap(m_read + offset)];
    }

    bool canDrop(u16 count = 1)
    {
        return requireLookahead(count);
    }
    Elem drop(u16 count = 1)
    {
        assert(canDrop(count));
        auto c = count;
        while (true) {
            --c;
            const auto last = dequeue();
            if (c == 0) return last;
        }
    }

    u64 count() const
    {
        if (full())
            return size;

        if (m_write >= m_read)
            return m_write - m_read; // element count?
        else
            return capacity() + (m_write - m_read);
    }

    bool requireLookahead(u16 lookahead)
    {
        if (lookahead >= size)
            return false;

        while (count() < lookahead and underlying().hasNext()) {
            const auto elem = underlying().next();
            enqueue(elem);
        }

        return count() >= lookahead;
    }
private:
    constexpr bool full() const { return m_full; }
    constexpr bool empty() const { return not full() and m_read == m_write; }
    constexpr u64 capacity() const { return size; }

    constexpr u64 wrap(u64 index) const { return index % capacity(); }
    constexpr void advance(u64 &field) { field = wrap(field + 1); }
    void enqueue(const Elem &elem)
    {
        assert(not full());
        m_lookahead[m_write] = elem;
        if (full()) advance(m_read);
        advance(m_write);
        m_full = m_read == m_write;
    }
    Elem dequeue()
    {
        assert(not empty());
        auto elem = m_lookahead[m_read];
        m_full = false;
        advance(m_read);
        return elem;
    }

private:
    Iterable m_underlying;
    Elem     m_lookahead[size];

    u64  m_read { 0 };
    u64  m_write { 0 };
    bool m_full { false };
};

}
