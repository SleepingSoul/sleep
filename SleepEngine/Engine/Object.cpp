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

Transform2D& Object::getTransform()
{
    return *getComponent<Transform2D>();
}

Transform2D const & Object::getTransform() const
{
    return *getComponent<Transform2D>();
}

Object::Object()
{
    addComponent<Transform2D>();
}

void Object::update(float dt)
{
    for (auto& component : m_components)
    {
        component->update(dt);
    }

    for (auto& child : m_children)
    {
        child->update(dt);
    }
}

END_NAMESPACE_SLEEP
