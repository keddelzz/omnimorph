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

template<typename Callback>
class EnabledScopeGuard
{
public:
    EnabledScopeGuard(Callback callback)
        : m_callback(callback)
    {}

    ~EnabledScopeGuard()
    {
        if (not m_disabled) {
            m_callback();
        }
    }

    void disable()
    {
        m_disabled = true;
    }

private:
    bool m_disabled { false };
    Callback m_callback;
};

template<typename Callback>
class DisabledScopeGuard
{
public:
    DisabledScopeGuard(Callback callback)
        : m_callback(callback)
    {}

    ~DisabledScopeGuard()
    {
        if (m_enabled) {
            m_callback();
        }
    }

    void enable()
    {
        m_enabled = true;
    }

private:
    bool m_enabled { false };
    Callback m_callback;
};