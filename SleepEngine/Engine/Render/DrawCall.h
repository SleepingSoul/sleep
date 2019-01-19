#pragma once

class DrawCall
{
public:
    DrawCall(Texture* texture, glm::vec2 position, glm::vec2 topLeftUV, glm::vec2 downRightUV, Layer layer);

    Texture* getTexture() const { return m_texture; }
    glm::vec2 getPosition() const { return m_position; }
    glm::vec2 getTopLeftUV() const { return m_topLeftUV; }
    glm::vec2 getDownRightUV() const { return m_downRightUV; }
    Layer getLayer() const { return m_layer; }

private:
    NotOwnedPtr <Texture> m_texture;
    glm::vec2 m_position;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
    Layer m_layer;
};
