#include "stdafx.h"
#include "Object.h"
#include <Engine/GameTemplate/Game.h>

BEGIN_NAMESPACE_SLEEP

Component* Object::addComponent(ComponentsContainer::value_type&& component)
{
    component->setParent(this);
    Component* const handle = component.get();
    m_components.emplace_back(std::move(component));
    return handle;
}

void Object::update(float dt)
{
    for (auto& component : m_components)
    {
        component->update(dt);
    }
}

END_NAMESPACE_SLEEP
