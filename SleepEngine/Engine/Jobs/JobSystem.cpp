#include "stdafx.h"

BEGIN_NAMESPACE_SLEEP

namespace
{
    constexpr unsigned ThreadsLeftAlone = 1;
}

unsigned threadCount()
{
    return std::max(std::thread::hardware_concurrency() - ThreadsLeftAlone, 0u);
}

//struct E
//{
//    E() = default;
//    E(E&&) = default;
//
//    bool m_isSet {false};
//    std::mutex m_mutex;
//    std::condition_variable m_condition;
//};
//
//struct A
//{
//    A(JobSystem::JobQueue& r) : m_ref(r) {}
//    A(const A&) = delete;
//    A(A&&) = default;
//
//    std::thread m_thread;
//    JobSystem::JobQueue& m_ref;
//    E m_workAvailable;
//};

JobSystem::JobSystem()
    : m_jobAvailable(threadCount())
{
    for (size_t i = 0, count = threadCount(); i < count; i++)
    {
        m_workerThreads.emplace_back(m_jobQueue, m_jobAvailable.at(i));
    }
}

END_NAMESPACE_SLEEP
