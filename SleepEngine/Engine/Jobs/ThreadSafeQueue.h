#pragma once

BEGIN_NAMESPACE_SLEEP

// T must be copyable
template <class T>
class ThreadSafeQueue
{
public:
    using LockGuard = std::lock_guard<std::mutex>;

    // if empty returns false
    // else moves front to popped and pops it from queue
    bool tryPop(T& popped)
    {
        LockGuard lk(m_mutex);

        if (m_queue.empty())
        {
            return false;
        }
        popped = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

    template< class... Args>
    void push(Args&&... arguments)
    {
        LockGuard lk(m_mutex);
        m_queue.emplace(std::forward<Args>(arguments)...);
    }

private:
    std::mutex m_mutex;
    std::queue<T> m_queue;
};

END_NAMESPACE_SLEEP

