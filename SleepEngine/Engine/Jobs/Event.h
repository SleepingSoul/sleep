#pragma once

BEGIN_NAMESPACE_SLEEP

class Event
{
    using LockGuard = std::lock_guard<std::mutex>;
public:
    inline void waitAndReset()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock,[&]()->bool{ return m_isSet; });
        m_isSet = false;
    }

    inline void signal()
    {
        ThreadSafeSet(true);
        m_condition.notify_all();
    }
	
    inline void reset()
    {
        ThreadSafeSet(false);
    }

    inline bool IsSet() const { return m_isSet; }

private:
    bool m_isSet {false};
    std::mutex m_mutex;
    std::condition_variable m_condition;

    void ThreadSafeSet(bool value)
    {
        if (m_isSet == value)
        {
            return;
        }
        LockGuard lk(m_mutex);
        m_isSet = value;
    }
};

END_NAMESPACE_SLEEP
