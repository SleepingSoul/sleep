// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class RigidBody : public Component
{
public:
    using Base = Component;

    enum class Type: unsigned char
    {
          Rectangle = 0
        , Ellipse
    };

    RigidBody() noexcept(true);

    GET_SET(glm::vec2, getSize, setSize, m_size)
    GET_SET(glm::vec2, getVelocity, setVelocity, m_velocity)
    GET_SET(float, getMass, setMass, m_mass)

private:
    glm::vec2 m_size;
    glm::vec2 m_velocity;
    float m_mass;
};

END_NAMESPACE_SLEEP
