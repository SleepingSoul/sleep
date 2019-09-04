#include "stdafx.h"
#include "JobSystem.h"

BEGIN_NAMESPACE_SLEEP

namespace
{
unsigned const ThreadsLeftAlone = 1;
}

enum class E
{
    E
};

JobSystem::JobSystem()
    : JobSystem(JobSystem::getWorkerThreadCount())
{}

JobSystem::JobSystem(size_t workerThreadCount)
    : m_jobAvailableEvents(workerThreadCount)
{
    if (workerThreadCount == 0)
    {
        return;
    }

    // TODO: add render thread
    JobQueue& genericQueue = m_affinityToQueues[JobAffinity::Generic];

    m_jobThreads.reserve(workerThreadCount);
    for (size_t i = 0; i < workerThreadCount; i++)
    {
        m_jobThreads.emplace_back(genericQueue, m_jobAvailableEvents.at(i), m_shutdownRequested);
        m_jobThreads.at(i).start();
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
    for (auto& thread : m_jobThreads)
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

size_t JobSystem::getWorkerThreadCount()
{
    return getWorkerThreadCount(*globalEngineConfig());
}

size_t JobSystem::getWorkerThreadCount(EngineConfig const& config)
{
    // all
    size_t threadCount = config.getData().ThreadsCount;

    if (threadCount == -1)
    {
        threadCount = std::thread::hardware_concurrency();
    }

    size_t const workerThreadCount = std::max(threadCount - ThreadsLeftAlone, 0u);
    return workerThreadCount;
}

END_NAMESPACE_SLEEP
