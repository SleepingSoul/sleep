#include "stdafx.h"
#include "JobSystem.h"

BEGIN_NAMESPACE_SLEEP

namespace
{
    constexpr unsigned ThreadsLeftAlone = 1;
}

unsigned workerThreadCount()
{
    return 1;
    //return std::max(std::thread::hardware_concurrency() - ThreadsLeftAlone, 0u);
}

JobSystem::JobSystem()
    : m_jobAvailable(workerThreadCount())
{
    if (workerThreadCount() == 0)
    {
        return;
    }

    // using [] for default constructing queues, as it is the only way for non-movable and non-copyable objects
    //JobQueue& renderQueue = m_affinityToQueues[JobAffinity::Render];
    //m_workerThreads.emplace_back(renderQueue, m_jobAvailable.at(0));

    JobQueue& genericQueue = m_affinityToQueues[JobAffinity::Generic];
    for (size_t i = 0; i < workerThreadCount(); i++)
    {
        m_jobThreads.emplace_back(genericQueue, m_jobAvailable.at(i), m_shutdownRequested);
    }
}

JobSystem::~JobSystem()
{
    // wake up sleeping threads, so that they can finish
    m_shutdownRequested = true;

    for (auto& event : m_jobAvailable)
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

    for (auto& event : m_jobAvailable)
    {
        event.signal();
    }
}

END_NAMESPACE_SLEEP
