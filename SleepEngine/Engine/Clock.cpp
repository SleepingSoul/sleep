#include "stdafx.h"
#include "Clock.h"
#include <Engine/Timer.h>


BEGIN_NAMESPACE_SLEEP

Clock::Clock(float fps)
    : m_desiredFrameTime(1.f / fps)
    , m_restrictFPS(false)
{
}

void Clock::frameStart(GameSystem system)
{
    auto it = m_deltaTimes.find(system);



    //DeltaTimeData& deltaTimeData = m_deltaTimes.at(

    //m_frameStartTime = glfwGetTime();
    updateTimers();
}

void Clock::frameEnd(GameSystem system)
{
    //auto const frameEndTime = glfwGetTime();
    //auto frameTime = static_cast <float>(frameEndTime - m_frameStartTime);

    //if (m_restrictFPS && frameTime < m_desiredFrameTime)
    //{
    //    EASY_BLOCK("Sleeping to sync FPS", profiler::colors::Amber);

    //    auto const millisecondsToSleep = 1000.f * (m_desiredFrameTime - frameTime);
    //    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast <int>(std::floor(millisecondsToSleep))));
    //    frameTime = m_desiredFrameTime;
    //    EASY_END_BLOCK;
    //}

    //*m_lastDT = frameTime;
    //if (++m_lastDT == m_lastDTs.end())
    //{
    //    m_lastDT = m_lastDTs.begin();
    //}
    //float const dt = std::accumulate(m_lastDTs.cbegin(), m_lastDTs.cend(), 0.f) / m_lastDTs.size();
    //m_amortizedDT.store(dt);
}

float Clock::calculateFPS() const
{
    return 1.f; // / m_amortizedDT;
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
        //timer->update(m_amortizedDT);
    }
}

END_NAMESPACE_SLEEP
