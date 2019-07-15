#include "stdafx.h"
#include "UpdateJob.h"
#include <Engine/Render/UpdateRenderBridge.h>
#include <Engine/Jobs/JobSystem.h>

BEGIN_NAMESPACE_SLEEP

std::unique_ptr<DelegateJob> createUpdateJob()
{
    auto executer = [] 
    {
        getGlobalClock().frameStart(GameSystem::Update);

        EASY_BLOCK("Scene update", profiler::colors::Amber100);
        globalEntityManager().update(getGlobalClock().getDT(GameSystem::Update));
        EASY_END_BLOCK;

        Game::instance().getRenderBridge().renewLastUpdatedData();
        globalJobSystem().schedule(createUpdateJob());

        getGlobalClock().frameEnd(GameSystem::Update);
    };

    return std::make_unique<DelegateJob>(executer);
}

END_NAMESPACE_SLEEP