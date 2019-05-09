#pragma once
#include <Engine/Jobs/ThreadSafeQueue.h>
#include <Engine/Jobs/Job.h>
#include <Engine/Jobs/Event.h>

BEGIN_NAMESPACE_SLEEP

class JobThread
{
public:
    using JobQueue = ThreadSafeQueue<std::unique_ptr<Job>>;

    // must pass Event because it cannot be part of thread -
    // thread must be movable to support addition to vector, and Event is neithre movable nor copyable,
    // so must be stored in a static default constructed vector somewhere else
    JobThread(JobQueue& jobQueue, Event& workAvailable, bool& shutdownRequested);

    REF_GETTER(getWorkAvailable, m_workAvailable);

    // called from the worker thread, before polling
    virtual void init() {}

    void join() { m_thread.join(); }
    bool joinable() const { return m_thread.joinable(); }

private:
    Event& m_workAvailable;
    bool& m_shutdownRequested;
    JobQueue& m_jobQueue;
    // m_thread depends on m_workAvailable, m_shutdownRequested and m_jobQueue
    // as it is initialized in init list, those 3 must be declared on top of it
    std::thread m_thread;

    // continuosly takes and executes jobs from job system
    void pollAndExecuteJobs();
};

END_NAMESPACE_SLEEP

