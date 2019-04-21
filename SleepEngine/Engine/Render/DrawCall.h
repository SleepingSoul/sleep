// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Object;

class DrawCall
{
public:
    DrawCall(Transform2DData const& transform, Texture* texture, glm::vec2 topLeftUV, glm::vec2 downRightUV, Color color)
        noexcept(std::is_nothrow_constructible_v <Transform2DData>);

    CONST_REF_GETTER(getTransform, m_transform)
    GETTER(getTexture, m_texture)
    GETTER(getTopLeftUV, m_topLeftUV)
    GETTER(getDownRightUV, m_downRightUV)
    GETTER(getColor, m_color)

private:
    Transform2DData m_transform;
    NotOwnedPtr <Texture> m_texture;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
    Color m_color;
};

inline bool operator <(DrawCall const& left, DrawCall const& right)
{
    return left.getTransform().Layer < right.getTransform().Layer;
}

END_NAMESPACE_SLEEP
