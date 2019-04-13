// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

struct Transform2DData
{
public:
    Transform2DData(glm::vec2 scale = {1.f, 1.f},
        glm::vec2 position = {0.f, 0.f},
        glm::vec2 size = {1.f, 1.f},
        Layer layer = 1,
        float rotation = 0.f) noexcept(true);

    GET_SET(glm::vec2, getScale, setScale, m_scale)
    GET_SET(glm::vec2, getPosition, setPosition, m_position)
    GET_SET(glm::vec2, getSize, setSize, m_size)
    GET_SET(Layer, getLayer, setLayer, m_layer)
    GET_SET(float, getRotation, setRotation, m_rotation)

private:
    glm::vec2 m_scale;
    glm::vec2 m_position;
    glm::vec2 m_size;
    Layer m_layer;
    float m_rotation;
};

END_NAMESPACE_SLEEP
