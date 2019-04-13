#include "stdafx.h"
#include "Object.h"
#include <Engine/EngineConfig.h>
#include <Engine/GameTemplate/Game.h>

BEGIN_NAMESPACE_SLEEP

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

END_NAMESPACE_SLEEP
