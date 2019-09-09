#include "stdafx.h"
#include "UpdateJob.h"
#include <Engine/Render/UpdateRenderBridge.h>
#include <Engine/Jobs/JobSystem.h>

BEGIN_NAMESPACE_SLEEP

std::unique_ptr<DelegateJob> createUpdateJob()
{
    auto executer = [] 
    {
        getGlobalClock().updateFrameStart();
        getGlobalClock().updateTimers();

        EASY_BLOCK("Scene update", profiler::colors::Amber100);
        globalEntityManager().update(getGlobalClock().getUpdateDT());
        EASY_END_BLOCK;

        Game::instance().getRenderBridge().renewLastUpdatedData();
        globalJobSystem().schedule(createUpdateJob());

        getGlobalClock().updateFrameEnd();
    };

    return std::make_unique<DelegateJob>(executer, JobAffinity::Generic);
}

END_NAMESPACE_SLEEP