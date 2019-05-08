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

JobSystem::JobSystem()
    : m_jobAvailable(threadCount())
{
    for (size_t i = 0, count = threadCount(); i < count; i++)
    {
        m_workerThreads.emplace_back(m_jobQueue, m_jobAvailable.at(i));
    }
}

END_NAMESPACE_SLEEP
