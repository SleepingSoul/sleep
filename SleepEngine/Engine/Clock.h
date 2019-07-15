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
    DeltaTimeData<std::atomic<float>> m_updateDeltaTime;

    float m_desiredFrameTime;
    bool m_restrictFPS;

    template <class TDeltaTime>
    static void frameStart(DeltaTimeData<TDeltaTime>& deltaTimeData)
    {
        deltaTimeData.FrameStartTime = glfwGetTime();
    }

    template <class TDeltaTime>
    void frameEnd(DeltaTimeData<TDeltaTime>& deltaTimeData)
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
};

END_NAMESPACE_SLEEP

