// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Renderer : public Component
{
public:
    using Base = Component;

    Renderer() noexcept(true);

    void update(float dt) override;

    REF_GET_SET(Color, getColor, setColor, m_color)
    GET_SET(glm::vec2, getTopLeftUV, setTopLeftUV, m_topLeftUV)
    GET_SET(glm::vec2, getDownRightUV, setDownRightUV, m_downRightUV)
    GET_SET(Texture*, getTexture, setTexture, m_texture)

private:
    Color m_color;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
    NotOwnedPtr <Texture> m_texture;
};

END_NAMESPACE_SLEEP
