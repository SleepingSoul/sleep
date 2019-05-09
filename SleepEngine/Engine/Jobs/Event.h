#pragma once

BEGIN_NAMESPACE_SLEEP

class Event
{
    using LockGuard = std::lock_guard<std::mutex>;
public:
    Event() = default;
    Event(Event&&) = default;

    inline void waitAndReset()
    {
        std::unique_lock<std::mutex> lk(m_mutex);
        assert(lk);
        m_condition.wait(lk, [this] { return m_isSet; });
        assert(lk);
        m_isSet = false;
    }

    inline void signal()
    {
        threadSafeSet(true);
        m_condition.notify_all();
    }
	
    inline void reset()
    {
        threadSafeSet(false);
    }

    inline bool IsSet() const { return m_isSet; }

private:
    bool m_isSet {false};
    std::mutex m_mutex;
    std::condition_variable m_condition;

    void threadSafeSet(bool value)
    {
        LockGuard lk(m_mutex);
        if (m_isSet == value)
        {
            return;
        }
        m_isSet = value;
    }
};

END_NAMESPACE_SLEEP
