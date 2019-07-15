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

void Clock::updateTimers()
{
    for (auto* const timer : m_timers)
    {
        // timers tick in the update timeline
        timer->update(m_updateDeltaTime.AmortizedDt);
    }
}

END_NAMESPACE_SLEEP
