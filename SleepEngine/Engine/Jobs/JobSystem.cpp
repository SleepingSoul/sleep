#include "stdafx.h"
#include "JobSystem.h"

BEGIN_NAMESPACE_SLEEP

namespace
{
    constexpr unsigned ThreadsLeftAlone = 1;
}

unsigned workerThreadCount()
{
    return std::max(std::thread::hardware_concurrency() - ThreadsLeftAlone, 0u);
}

JobSystem::JobSystem()
    : m_jobAvailable(workerThreadCount())
{
    if (workerThreadCount() == 0)
    {
        return;
    }

    // using [] for default constructing queues, as it is the only way for non-movable and non-copyable objects
    JobQueue& renderQueue = m_affinityToQueues[JobAffinity::Render];
    m_workerThreads.emplace_back(renderQueue, m_jobAvailable.at(0));

    JobQueue& genericQueue = m_affinityToQueues[JobAffinity::Generic];
    for (size_t i = 1, count = workerThreadCount(); i < count; i++)
    {
        m_workerThreads.emplace_back(genericQueue, m_jobAvailable.at(i));
    }
}

END_NAMESPACE_SLEEP
