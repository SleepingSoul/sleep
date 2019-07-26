#include "stdafx.h"
#include "Clock.h"
#include <Engine/Timer.h>


BEGIN_NAMESPACE_SLEEP

Clock::Clock(float fps)
    : m_desiredFrameTime(1.f / fps)
    , m_restrictFPS(false)
{}


float Clock::calculateFPS() const
{
    return 1.f / m_renderDeltaTime.AmortizedDt;
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

void Clock::frameStart(DeltaTimeData<float>& deltaTimeData)
{
    deltaTimeData.FrameStartTime = glfwGetTime();
}

void Clock::frameEnd(DeltaTimeData<float>& deltaTimeData)
{
    double const frameEndTime = glfwGetTime();
    float frameTime = static_cast <float>(frameEndTime - deltaTimeData.FrameStartTime);

    if (m_restrictFPS && frameTime < m_desiredFrameTime)
    {
        EASY_BLOCK("Sleeping to sync FPS", profiler::colors::Amber);

        float const millisecondsToSleep = 1000.f * (m_desiredFrameTime - frameTime);
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast <int>(std::floor(millisecondsToSleep))));
        frameTime = m_desiredFrameTime;
        EASY_END_BLOCK;
    }

    *deltaTimeData.LastDt = frameTime;
    if (++deltaTimeData.LastDt == deltaTimeData.LastDts.end())
    {
        deltaTimeData.LastDt = deltaTimeData.LastDts.begin();
    }
    float const dt = std::accumulate(deltaTimeData.LastDts.cbegin(), deltaTimeData.LastDts.cend(), 0.f) / deltaTimeData.LastDts.size();
    deltaTimeData.AmortizedDt = dt;
}

void Clock::updateTimers()
{
    for (auto* const timer : m_timers)
    {
        // timers tick in the update timeline
        timer->update(m_updateDeltaTime.AmortizedDt);
    }
}

END_NAMESPACE_SLEEP
