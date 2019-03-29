#include "stdafx.h"
#include "Object.h"
#include <Engine/EngineConfig.h>
#include <Engine/GameTemplate/Game.h>

BeginNamespaceSleep

Object::Object() noexcept(std::is_nothrow_constructible_v <Transform2D> && std::is_nothrow_constructible_v <ComponentsContainer>)
    : m_transform{
        glm::vec2(1.f, 1.f), // scale
        glm::vec2(0.f, 0.f), // pos
        glm::vec2(1.f, 1.f), // size
        1,                   // layer
        0.f                  // rotation
        }
    , m_color(1.f, 1.f, 1.f, 1.f)
    , m_topLeftUV(0.f, 0.f)
    , m_downRightUV(1.f, 1.f)
    , m_texture(nullptr)
{}

void Object::setLayer(Layer const layer)
{
    assertion(layer < slp::MaxLayer, "Layer is more then 'MaxLayer' defined in EngineConfig");
    m_transform.layer = layer;
}

void Object::setUV(float const topLeftX, float const topLeftY, float const downRightX, const float downRightY)
{
    m_topLeftUV = { topLeftX, topLeftY };
    m_downRightUV = { downRightX, downRightY };
}

void Object::addComponent(ComponentsContainer::value_type&& component)
{
    component->setParent(this);
    m_components.emplace_back(std::move(component));
}

void Object::update(float dt)
{
    for (auto& component : m_components)
    {
        component->update(dt);
    }
}

EndNamespaceSleep
