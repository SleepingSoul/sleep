// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Renderer : public Component
{
public:
    using Base = Component;

    Renderer() noexcept(true);

    void update(float dt) override;

    Color getColor() const { return m_color; }
    void setColor(Color color) { m_color = color; }

    glm::vec2 getTopLeftUV() const { return m_topLeftUV; }
    void setTopLeftUV(glm::vec2 uv) { m_topLeftUV = uv; }

    glm::vec2 getDownRightUV() const { return m_downRightUV; }
    void setDownRightUV(glm::vec2 uv) { m_downRightUV = uv; }

    Texture* getTexture() const { return m_texture; }
    void setTexture(Texture* texture) { m_texture = texture; }

private:
    Color m_color;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
    NotOwnedPtr <Texture> m_texture;
};

EndNamespaceSleep
