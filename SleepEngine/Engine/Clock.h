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

    // method duplication is needed, as the delta time datas are of different type for render and update
    void updateFrameStart() { frameStart(m_updateDeltaTime); }
	// also sleeps if m_restrictFPS is set and 
    // the frame was to short to sustain desired fps
    void updateFrameEnd() { frameEnd(m_updateDeltaTime); }
    float getUpdateDT() const { return m_updateDeltaTime.AmortizedDt; }

    void renderFrameStart() { frameStart(m_renderDeltaTime); }
    // also sleeps if m_restrictFPS is set and 
    // the frame was to short to sustain desired fps
    void renderFrameEnd() { frameEnd(m_renderDeltaTime); }
    float getRenderDT() const { return m_renderDeltaTime.AmortizedDt; }

    void updateTimers();
    void setFPS(float fps) { m_desiredFrameTime = 1.f / fps; }
    SETTER(bool, setRestrictFPS, m_restrictFPS)

    // fps of the render
    float calculateFPS() const;

    void registerTimer(Timer* timer);
    void unregisterTimer(Timer* timer);

private:
    TimersContainerType m_timers;

    DeltaTimeData<float> m_renderDeltaTime;
    DeltaTimeData<float> m_updateDeltaTime;

    float m_desiredFrameTime;
    bool m_restrictFPS;

    static void frameStart(DeltaTimeData<float>& deltaTimeData);
    void frameEnd(DeltaTimeData<float>& deltaTimeData);

};

END_NAMESPACE_SLEEP

