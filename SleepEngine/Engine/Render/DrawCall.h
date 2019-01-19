#pragma once

class DrawCall
{
public:
    // saves current texture state
    DrawCall(Texture* texture, Layer const layer)
        : m_texture(texture)
        , m_topLeftUV(texture->getTopLeftUV())
        , m_downRightUV(texture->getDownRightUV())
        , m_layer(layer)
    {}

    Texture* getTexture() const { return m_texture; }
    glm::vec2 getTopLeftUV() const { return m_topLeftUV; }
    glm::vec2 getDownRightUV() const { return m_downRightUV; }

private:
    NotOwnedPtr <Texture> m_texture;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
    Layer m_layer;
};
