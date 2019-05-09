#pragma once
#include <Engine/Jobs/JobAffinity.h>

BEGIN_NAMESPACE_SLEEP

class Job
{
public:
    Job(JobAffinity affinity = JobAffinity::Generic)
        : m_affinity(affinity) {}
    
    JobAffinity getAffinity() const { return m_affinity; }
    virtual void execute() = 0;

private:
    JobAffinity m_affinity;
};

class DelegateJob : public Job
{
    using Base = Job;
public:
    DelegateJob(std::function<void()> executer, JobAffinity affinity = JobAffinity::Generic)
        : Base(affinity)
        , m_executer(std::move(executer))
    {}

    void execute() override
    {
        m_executer();
    }

private:
    std::function<void()> m_executer;
};

END_NAMESPACE_SLEEP
