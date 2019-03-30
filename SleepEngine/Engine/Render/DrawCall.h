// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Object;

class DrawCall
{
public:
    DrawCall(Transform2DData const& transform, Texture* texture, glm::vec2 topLeftUV, glm::vec2 downRightUV, Color color)
        noexcept(std::is_nothrow_constructible_v <Transform2DData>);

    Transform2DData const& getTransform() const { return m_transform; }
    Texture* getTexture() const { return m_texture; }
    glm::vec2 getTopLeftUV() const { return m_topLeftUV; }
    glm::vec2 getDownRightUV() const { return m_downRightUV; }
    Color getColor() const { return m_color; }

private:
    Transform2DData m_transform;
    NotOwnedPtr <Texture> m_texture;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
    Color m_color;
};

inline bool operator <(DrawCall const& left, DrawCall const& right)
{
    return left.getTransform().layer < right.getTransform().layer;
}

EndNamespaceSleep
