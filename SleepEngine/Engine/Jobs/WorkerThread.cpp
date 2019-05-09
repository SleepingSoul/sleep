#include "stdafx.h"
#include "WorkerThread.h"

BEGIN_NAMESPACE_SLEEP

WorkerThread::WorkerThread(JobQueue& jobQueue, Event& workAvailable)
    : m_jobQueue(jobQueue)
    , m_workAvailable(workAvailable)
    , m_thread([this] 
    { 
        init();
        pollAndExecuteJobs(); 
    })
{}

void WorkerThread::pollAndExecuteJobs()
{
    while(true)
    {
        m_workAvailable.waitAndReset();

        std::unique_ptr<Job> availableJob;
        while(m_jobQueue.tryPop(availableJob))
        {
            //availableJob->execute();
        }
    }
}

END_NAMESPACE_SLEEP