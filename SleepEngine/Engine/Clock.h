// Copyright 2019 Tihran Katolikian

#pragma once
#include <Engine/DeltaTimeData.h>
#include <Engine/Systems/Systems.h>

BEGIN_NAMESPACE_SLEEP

class Timer;

// calculates and stores DT,
// stores and updates timers
class Clock
{
    FORBID_COPY_AND_MOVE(Clock)
public:
    using TimersContainerType = std::vector <Timer*>;

    Clock(float fps);

    // TODO: mb its worth hardcoding a switch to get rid of a map, or using a vector of pairs for performance
    // but elegance is more importante now
    void frameStart(GameSystem system);
	// also sleeps if m_restrictFPS is set and 
    // the frame was to short to sustain desired fps
    void frameEnd(GameSystem system);
    float getDT(GameSystem system) const;

    void updateTimers();


    void setFPS(float fps) { m_desiredFrameTime = 1.f / fps; }

    SETTER(bool, setRestrictFPS, m_restrictFPS)

    // fps of the render
    float calculateFPS() const;

    void registerTimer(Timer* timer);
    void unregisterTimer(Timer* timer);

private:
    TimersContainerType m_timers;

    std::unordered_map<GameSystem, DeltaTimeData> m_deltaTimes;

    float m_desiredFrameTime;
    bool m_restrictFPS;
};

END_NAMESPACE_SLEEP
