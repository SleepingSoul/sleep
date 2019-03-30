// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Timer;

class Clock
{
    FORBID_COPY_AND_MOVE(Clock)
public:
    using DTStorageContainerType = std::array <float, 10>;
    using TimersContainerType = std::vector <Timer*>;

    Clock(float fps);

    void frameStart();
	// also sleeps if m_restrictFPS is set and 
    // also sleeps if m_restrictFPS is set and
    // the frame was to short to sustain desired fps has passed since last frame
    void frameEnd();
    float getDT() const { return m_amortizedDT; }

    void setFPS(float fps) { m_desiredFrameTime = 1.f / fps; }
    void setRestrictFPS(bool restrictFPS) { m_restrictFPS = restrictFPS; }

    float calculateFPS() const;

    void registerTimer(Timer* timer);
    void unregisterTimer(Timer* timer);

private:
    void updateTimers();

    DTStorageContainerType m_lastDTs;
    DTStorageContainerType::iterator m_lastDT;

    TimersContainerType m_timers;

    double m_frameStartTime;
    float m_amortizedDT;

    float m_desiredFrameTime;
    bool m_restrictFPS;
};

EndNamespaceSleep
