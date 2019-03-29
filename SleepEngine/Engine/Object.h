// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Object
{
public:
    using ComponentsContainer = std::vector <std::unique_ptr <Component>>;

    Object() noexcept(std::is_nothrow_constructible_v <Transform2D> && std::is_nothrow_constructible_v <ComponentsContainer>);

    Color getColor() const { return m_color; }
    Color& modifyColor() { return m_color; }
    void setColor(Color const color) { m_color = color; }

    glm::vec2 getScale() const { return m_transform.scale; }
    void setScale(glm::vec2 const scale) { m_transform.scale = scale; }

    glm::vec2 getPosition() const { return m_transform.position; }
    void setPosition(glm::vec2 const position) { m_transform.position = position; }

    glm::vec2 getSize() const { return m_transform.size; }
    void setSize(glm::vec2 const size) { m_transform.size = size; }

    float getX() const { return m_transform.position.x; }
    void setX(float x) { m_transform.position.x = x; }

    float getY() const { return m_transform.position.y; }
    void setY(float y) { m_transform.position.y = y; }

    Texture* getTexture() const { return m_texture; }
    void setTexture(Texture* const texture) { m_texture = texture; }

    Layer getLayer() const { return m_transform.layer; }
    void setLayer(Layer layer);

    glm::vec2 getTopLeftUV() const { return m_topLeftUV; }
    void setTopLeftUV(glm::vec2 const uv) { m_topLeftUV = uv; }

    glm::vec2 getDownRightUV() const { return m_downRightUV; }
    void setDownRightUV(glm::vec2 const uv) { m_downRightUV = uv; }

    void setUV(float topLeftX, float topLeftY, float downRightX, float downRightY);

    float getRotation() const { return m_transform.rotation; }
    void setRotation(float const rotation) { m_transform.rotation = rotation; }

    void addComponent(ComponentsContainer::value_type&& component);

    virtual void update(float dt);

private:
    ComponentsContainer m_components;

    Transform2D m_transform;

    Color m_color;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
    NotOwnedPtr <Texture> m_texture;
};

EndNamespaceSleep
