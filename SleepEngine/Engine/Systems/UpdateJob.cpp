#include "stdafx.h"
#include "UpdateJob.h"
#include <Engine/Render/UpdateRenderBridge.h>
#include <Engine/Jobs/JobSystem.h>

BEGIN_NAMESPACE_SLEEP

UpdateJob::UpdateJob(slp::ObjectTree& objectTree)
   : m_objectTree(objectTree)
{}

void UpdateJob::execute()
{
    auto& clock = getGlobalClock();
    clock.frameStart();

    EASY_BLOCK("Scene update", profiler::colors::Amber100);
    m_objectTree.update(clock.getDT());
    EASY_END_BLOCK;

    Game::instance().getRenderBridge().renewLastUpdatedData();
    globalJobSystem().schedule(std::make_unique<UpdateJob>(m_objectTree));

    clock.frameEnd();
}

END_NAMESPACE_SLEEP