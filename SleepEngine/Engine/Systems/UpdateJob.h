#pragma once
#include <Engine/Jobs/Job.h>

BEGIN_NAMESPACE_SLEEP

class UpdateJob : public Job
{
public:
    UpdateJob(slp::ObjectTree& objectTree);

    void execute() override;

private:
    ObjectTree& m_objectTree;
};

END_NAMESPACE_SLEEP
