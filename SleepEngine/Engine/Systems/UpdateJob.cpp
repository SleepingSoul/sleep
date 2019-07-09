#include "stdafx.h"
#include "UpdateJob.h"
#include <Engine/Render/UpdateRenderBridge.h>
#include <Engine/Jobs/JobSystem.h>

BEGIN_NAMESPACE_SLEEP

std::unique_ptr<DelegateJob> createUpdateJob()
{
    auto executer = [] 
    {
        EASY_BLOCK("Scene update", profiler::colors::Amber100);
        globalEntityManager().update(getGlobalClock().getDT());
        EASY_END_BLOCK;

        Game::instance().getRenderBridge().renewLastUpdatedData();
        globalJobSystem().schedule(createUpdateJob());
    };

    return std::make_unique<DelegateJob>(executer);
}

END_NAMESPACE_SLEEP