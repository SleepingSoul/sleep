#include "stdafx.h"
#include "JobThread.h"

BEGIN_NAMESPACE_SLEEP

JobThread::JobThread(JobQueue& jobQueue, Event& workAvailable, std::atomic<bool> const& shutdownRequested)
    : m_jobQueue(jobQueue)
    , m_workAvailable(workAvailable)
    , m_shutdownRequested(shutdownRequested)
    , m_thread([this]
    { 
        init();
        pollAndExecuteJobs(); 
    })
{}

void JobThread::pollAndExecuteJobs()
{
    while(true)
    {
        m_workAvailable.waitAndReset();

        if (m_shutdownRequested.load())
        {
            break;
        }

        std::unique_ptr<Job> availableJob;
        while(m_jobQueue.tryPop(availableJob))
        {
            // extra check, because we may be stuck in the loop with pipelining jobs
            if (m_shutdownRequested.load())
            {
                return;
            }
            availableJob->execute();
        }
    }
}

END_NAMESPACE_SLEEP