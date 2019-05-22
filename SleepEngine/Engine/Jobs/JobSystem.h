#pragma once
#include <Engine/Jobs/JobThread.h>
#include <Engine/Jobs/Job.h>
#include <Engine/Jobs/ThreadSafeQueue.h>
#include <Engine/Jobs/Event.h>
#include <Engine/Jobs/JobAffinity.h>

BEGIN_NAMESPACE_SLEEP

// Job threads are spawned for each hardware thread minus 1 - for the main thread
class JobSystem
{
public:
    using JobQueue = ThreadSafeQueue<std::unique_ptr<Job>>;

    JobSystem();
    ~JobSystem();

    void schedule(std::unique_ptr<Job>&& job);
   

private:
    std::unordered_map<JobAffinity, JobQueue> m_affinityToQueues;
    std::vector<Event> m_jobAvailableEvents;
    std::vector<JobThread> m_jobThreads;
    bool m_shutdownRequested = false;
};

END_NAMESPACE_SLEEP

