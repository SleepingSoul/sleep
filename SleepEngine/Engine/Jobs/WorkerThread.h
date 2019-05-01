#pragma once
#include <Engine/Jobs/ThreadSafeQueue.h>
#include <Engine/Jobs/Job.h>
#include <Engine/Jobs/Event.h>

BEGIN_NAMESPACE_SLEEP

class WorkerThread
{
public:
    using JobQueue = ThreadSafeQueue<std::unique_ptr<Job>>;

    WorkerThread(JobQueue& jobQueue, Event& workAvailable);

    // continuosly takes and executes jobs from job system
    void startWorking();


private:
    std::thread m_thread;
    JobQueue& m_jobQueue;
    Event& m_workAvailable;
};

END_NAMESPACE_SLEEP

