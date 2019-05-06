#pragma once
#include <Engine/Jobs/ThreadSafeQueue.h>
#include <Engine/Jobs/Job.h>
#include <Engine/Jobs/Event.h>

BEGIN_NAMESPACE_SLEEP

class WorkerThread
{
public:
    using JobQueue = ThreadSafeQueue<std::unique_ptr<Job>>;

    // must pass Event because it cannot be part of thread -
    // thread must be movable to support addition to vector, and Event is neithre movable nor copyable,
    // so must be stored in a static default constructed vector somewhere else
    WorkerThread(JobQueue& jobQueue, Event& workAvailable);
    WorkerThread(WorkerThread&&) = default;
    //WorkerThread(WorkerThread const&) = delete;

    REF_GETTER(getWorkAvailable, m_workAvailable);

    // continuosly takes and executes jobs from job system
    void startWorking();


private:
    std::thread m_thread;
    JobQueue& m_jobQueue;
    Event& m_workAvailable;
};

END_NAMESPACE_SLEEP

