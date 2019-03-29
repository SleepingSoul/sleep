// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Transform2D : public Component
{
public:
    using Base = Component;

    Transform2D() noexcept(true);

    REF_GETTERS(getData, m_data);

    void update(float dt) override {}

private:
    Transform2DData m_data;
};

EndNamespaceSleep
