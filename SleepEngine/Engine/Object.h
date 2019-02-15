#pragma once

class Object : public Updator
{
public:
    Object() noexcept(true);

    Color getColor() const { return m_color; }
    Color& modifyColor() { return m_color; }
    void setColor(Color const color) { m_color = color; }

    glm::vec2 getScale() const { return m_scale; }
    void setScale(glm::vec2 const scale) { m_scale = scale; }

    glm::vec2 getPosition() const { return m_position; }
    void setPosition(glm::vec2 const position) { m_position = position; }

    glm::vec2 getSize() const { return m_size; }
    void setSize(glm::vec2 const size) { m_size = size; }

    Texture* getTexture() const { return m_texture; }
    void setTexture(Texture* const texture) { m_texture = texture; }

    Layer getLayer() const { return m_layer; }
    void setLayer(Layer const layer) { m_layer = layer; }

    glm::vec2 getTopLeftUV() const { return m_topLeftUV; }
    void setTopLeftUV(glm::vec2 const uv) { m_topLeftUV = uv; }

    glm::vec2 getDownRightUV() const { return m_downRightUV; }
    void setDownRightUV(glm::vec2 const uv) { m_downRightUV = uv; }

    void setUV(float topLeftX, float topLeftY, float downRightX, float downRightY);

    float getRotation() const { return m_rotation; }
    void setRotation(float const rotation) { m_rotation = rotation; }

    void render() override;

private:
    Color m_color;
    glm::vec2 m_scale;
    glm::vec2 m_position;
    glm::vec2 m_size;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
    NotOwnedPtr <Texture> m_texture;
    Layer m_layer;
    float m_rotation;
};
