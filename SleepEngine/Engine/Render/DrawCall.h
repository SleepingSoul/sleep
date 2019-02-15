// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Object;

class DrawCall
{
public:
    DrawCall(Object* object) noexcept(true);

    Texture* getTexture() const { return m_texture; }
    glm::vec2 getScale() const { return m_scale; }
    glm::vec2 getPosition() const { return m_position; }
    glm::vec2 getSize() const { return m_size; }
    glm::vec2 getTopLeftUV() const { return m_topLeftUV; }
    glm::vec2 getDownRightUV() const { return m_downRightUV; }
    Layer getLayer() const { return m_layer; }
    float getRotation() const { return m_rotation; }

private:
    NotOwnedPtr <Texture> m_texture;
    glm::vec2 m_scale;
    glm::vec2 m_position;
    glm::vec2 m_size;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
    Layer m_layer;
    float m_rotation;
};

inline bool operator <(DrawCall const& left, DrawCall const& right)
{
    return left.getTexture() > right.getTexture();
}

EndNamespaceSleep
