// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Clock
{
    ForbidCopyAndMove(Clock)
public:
    using DTStorageContainerType = std::array <float, 10>;

    Clock(float fps);

    void frameStart();
    void frameEnd();
    float getDT() const { return m_amortizedDT; }

    void setFPS(float fps) { m_desiredFrameTime = 1.f / fps; }
    void setRestrictFPS(bool restrictFPS) { m_restrictFPS = restrictFPS; }

    float calculateFPS() const;

private:
    DTStorageContainerType m_lastDTs;
    DTStorageContainerType::iterator m_lastDT;

    double m_frameStartTime;
    float m_amortizedDT;

    float m_desiredFrameTime;
    bool m_restrictFPS;
};

EndNamespaceSleep
