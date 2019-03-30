// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Timer
{
public:
    Timer();
    ~Timer();

    void every(float time, Callback callback);

    void update(float dt);

    void start() { m_isStarted = true; }
    void stop() { m_isStarted = false; }

private:
    Callback m_callback;
    float m_interval;
    float m_accumulator;

    bool m_isStarted;
};

EndNamespaceSleep
