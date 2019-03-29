#include "stdafx.h"
#include "Object.h"
#include <Engine/EngineConfig.h>
#include <Engine/GameTemplate/Game.h>

BeginNamespaceSleep

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
