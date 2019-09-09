#pragma once

BEGIN_NAMESPACE_SLEEP

class Event
{
public:
    Event() = default;
    Event(Event&&) = default;

    void waitAndReset()
    {
        std::unique_lock lk(m_mutex);
        m_condition.wait(lk, [this] { return m_isSet; });
        m_isSet = false;
    }

    void signal()
    {
        threadSafeSet(true);
        m_condition.notify_all();
    }
	
    void reset()
    {
        threadSafeSet(false);
    }

    bool IsSet() const { return m_isSet; }

private:
    bool m_isSet {false};
    std::mutex m_mutex;
    std::condition_variable m_condition;

    void threadSafeSet(bool value)
    {
        std::lock_guard lk(m_mutex);
        m_isSet = value;
    }
};

END_NAMESPACE_SLEEP
