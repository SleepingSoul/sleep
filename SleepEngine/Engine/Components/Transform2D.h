// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Transform2D : public Component
{
public:
    using Base = Component;

    Transform2D() noexcept(true);

    GET_SET(glm::vec2, getScale, setScale, m_data.Scale)
    GET_SET(glm::vec2, getPosition, setPosition, m_data.Position)
    GET_SET(glm::vec2, getSize, setSize, m_data.Size)
    GET_SET(Layer, getLayer, setLayer, m_data.Layer)
    GET_SET(float, getRotation, setRotation, m_data.Rotation)

    CONST_REF_GETTER(getData, m_data)

    void translate(glm::vec2 translation);
    void rotate(float rotation);

private:
    Transform2DData m_data;
};

END_NAMESPACE_SLEEP
