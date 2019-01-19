#pragma once

class Object : public Updator
{
public:
    Object();

    Color getColor() const { return m_color; }
    Color& modifyColor() { return m_color; }
    void setColor(Color const color) { m_color = color; }

    glm::vec2 getPosition() const { return m_position; }
    void setPosition(glm::vec2 const position) { m_position = position; }

    glm::vec2 getSize() const { return m_size; }
    void setSize(glm::vec2 const size) { m_size = size; }

    Texture* getTexture() const { return m_texture; }
    void setTexture(Texture* const texture) { m_texture = texture; }

    Layer getLayer() const { return m_layer; }
    void setLayer(Layer const layer) { m_layer = layer; }

    void render() override;

private:
    Color m_color;
    glm::vec2 m_position;
    glm::vec2 m_size;
    NotOwnedPtr <Texture> m_texture;
    Layer m_layer;
};
