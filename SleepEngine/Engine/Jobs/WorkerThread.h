#pragma once

BEGIN_NAMESPACE_SLEEP

class WorkerThread
{
public:
    void startWorking();


private:
    std::thread m_thread;
};

END_NAMESPACE_SLEEP

