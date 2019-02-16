#include "stdafx.h"
#include "Timer.h"


BeginNamespaceSleep

Timer::Timer()
    : m_accumulator(0.f)
    , m_interval(1.f)
{
    GameWindow::instance().getClock().registerTimer(this);
}

Timer::~Timer()
{
    GameWindow::instance().getClock().unregisterTimer(this);
}

void Timer::every(float time, Callback callback)
{
    m_interval = time;
    m_callback = std::move(callback);
}

void Timer::update(float dt)
{
    if (!m_isStarted)
    {
        return;
    }

    m_accumulator += dt;
    if (m_accumulator >= m_interval)
    {
        m_accumulator = 0.f;
        if (m_callback)
        {
            m_callback();
        }
    }
}

EndNamespaceSleep
