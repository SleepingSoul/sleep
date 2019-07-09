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
    : m_jobAvailableEvents(workerThreadCount())
{
    if (workerThreadCount() == 0)
    {
        return;
    }

    // TODO: add render thread

    JobQueue& genericQueue = m_affinityToQueues[JobAffinity::Generic];
    for (size_t i = 0; i < workerThreadCount(); i++)
    {
        m_jobThreads.emplace_back(genericQueue, m_jobAvailableEvents.at(i), m_shutdownRequested);
    }
}

JobSystem::~JobSystem()
{
    m_shutdownRequested = true;

    // wake up sleeping threads, so that they can finish
    for (auto& event : m_jobAvailableEvents)
    {
        event.signal();
    }
    for(auto& thread : m_jobThreads)
    {
        if (!thread.joinable())
        {
            LOG_AND_FAIL("a job thread is not joinable in job system dtor!");
            continue;
        }

        thread.join();
    }
}

void JobSystem::schedule(std::unique_ptr<Job>&& job)
{
    auto& queue = m_affinityToQueues.at(job->getAffinity());
    queue.push(std::move(job));

    for (auto& event : m_jobAvailableEvents)
    {
        event.signal();
    }
}

END_NAMESPACE_SLEEP
