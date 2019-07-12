#include "stdafx.h"
#include "Clock.h"
#include <Engine/Timer.h>


BEGIN_NAMESPACE_SLEEP

Clock::Clock(float fps)
    : m_desiredFrameTime(1.f / fps)
    , m_restrictFPS(false)
{
    m_deltaTimes.emplace(GameSystem::Render, DeltaTimeData());
    m_deltaTimes.emplace(GameSystem::Update, DeltaTimeData());
}

void Clock::frameStart(GameSystem system)
{
    DeltaTimeData* systemDt = nullptr;
    if (!tryGet(m_deltaTimes, system, systemDt))
    {
        return;
    }
    
    systemDt->FrameStartTime = glfwGetTime();
    updateTimers();
}

void Clock::frameEnd(GameSystem system)
{
    DeltaTimeData* systemDt = nullptr;
    if (!tryGet(m_deltaTimes, system, systemDt))
    {
        return;
    }

    double const frameEndTime = glfwGetTime();
    float frameTime = static_cast <float>(frameEndTime - systemDt->FrameStartTime);

    if (m_restrictFPS && frameTime < m_desiredFrameTime)
    {
        EASY_BLOCK("Sleeping to sync FPS", profiler::colors::Amber);

        auto const millisecondsToSleep = 1000.f * (m_desiredFrameTime - frameTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast <int>(std::floor(millisecondsToSleep))));
        frameTime = m_desiredFrameTime;
        EASY_END_BLOCK;
    }

    *systemDt->LastDt = frameTime;
    if (++systemDt->LastDt == systemDt->LastDts.end())
    {
        systemDt->LastDt = systemDt->LastDts.begin();
    }
    float const dt = std::accumulate(systemDt->LastDts.cbegin(), systemDt->LastDts.cend(), 0.f) / systemDt->LastDts.size();
    systemDt->AmortizedDt = dt;
}

float Clock::calculateFPS() const
{
    return m_deltaTimes.at(GameSystem::Render).AmortizedDt;
}

void Clock::registerTimer(Timer* timer)
{
    m_timers.push_back(timer);
}

void Clock::unregisterTimer(Timer* timer)
{
    auto it = std::find(m_timers.cbegin(), m_timers.cend(), timer);
    if (it == m_timers.cend())
    {
        assertion(false, "Attempt to unregister timer: timer not found");
        return;
    }

    m_timers.erase(it);
}

void Clock::updateTimers()
{
    for (auto* const timer : m_timers)
    {
        // timers tick in the update timeline
        timer->update(m_deltaTimes.at(GameSystem::Update).AmortizedDt);
    }
}

END_NAMESPACE_SLEEP
