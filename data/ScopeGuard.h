#pragma once

template<typename Callback>
class ScopeGuard
{
public:
    ScopeGuard(Callback callback)
        : m_callback(callback)
    {}

    ~ScopeGuard()
    {
        m_callback();
    }

private:
    Callback m_callback;
};