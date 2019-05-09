#include "stdafx.h"
#include "JobThread.h"

BEGIN_NAMESPACE_SLEEP

JobThread::JobThread(JobQueue& jobQueue, Event& workAvailable, bool& shutdownRequested)
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

        if (m_shutdownRequested)
        {
            break;
        }

        std::unique_ptr<Job> availableJob;
        while(m_jobQueue.tryPop(availableJob))
        {
            availableJob->execute();
        }
    }
}

END_NAMESPACE_SLEEP