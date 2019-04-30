// Copyright 2019 Tihran Katolikian

#pragma once

#include <Engine/Components/RelativeTransform.h>

BEGIN_NAMESPACE_SLEEP

class Transform2D : public Component
{
public:
    using Base = Component;

    Transform2D() noexcept(true);

    GET_SET(glm::vec2, getScale, setScale, m_data.Scale)
    GET_SET(glm::vec2, getPosition, setPosition, m_data.Position)
    GET_SET(glm::vec2, getSize, setSize, m_data.Size)
    GET_SET(LayerT, getLayer, setLayer, m_data.Layer)
    GET_SET(float, getRotation, setRotation, m_data.Rotation)

    // TODO: implement cached transform global data and change this
    GETTER(getGlobalPosition, getGlobalData().Position)
    GETTER(getGlobalRotation, getGlobalData().Rotation)

    Transform2DData getGlobalData() const;

    void translate(glm::vec2 translation);
    void rotate(float rotation);

private:
    RelativeTransform getRelativeTransform() const;

    Transform2DData m_data;
};

COMPONENT_SHORTCUTS(Transform2D, getTransform)

END_NAMESPACE_SLEEP
