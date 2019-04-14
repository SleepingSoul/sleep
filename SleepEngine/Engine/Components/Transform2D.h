// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Transform2D : public Component
{
public:
    using Base = Component;

    Transform2D() noexcept(true);

    REF_GETTERS(getData, m_data)
    void translate(glm::vec2 translation);
    void rotate(float rotation);

private:
    Transform2DData m_data;
};

END_NAMESPACE_SLEEP
