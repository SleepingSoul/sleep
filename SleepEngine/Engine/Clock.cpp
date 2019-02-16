#include "stdafx.h"
#include "Clock.h"


BeginNamespaceSleep

Clock::Clock(float fps)
    : m_desiredFrameTime(1.f / fps)
    , m_restrictFPS(false)
{
    std::fill(m_lastDTs.begin(), m_lastDTs.end(), m_desiredFrameTime);
    m_lastDT = m_lastDTs.begin();
}

void Clock::frameStart()
{
    m_frameStartTime = glfwGetTime();
}

void Clock::frameEnd()
{
    auto const frameEndTime = glfwGetTime();
    auto frameTime = static_cast <float>(frameEndTime - m_frameStartTime);

    if (m_restrictFPS && frameTime < m_desiredFrameTime)
    {
        frameTime = m_desiredFrameTime;
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast <int>(std::floor(m_desiredFrameTime - frameTime))));
    }

    *m_lastDT = frameTime;
    if (++m_lastDT == m_lastDTs.end())
    {
        m_lastDT = m_lastDTs.begin();
    }
    m_amortizedDT = std::accumulate(m_lastDTs.cbegin(), m_lastDTs.cend(), 0.f) / m_lastDTs.size();
}

float Clock::calculateFPS() const
{
    return 1.f / m_amortizedDT;
}

EndNamespaceSleep
