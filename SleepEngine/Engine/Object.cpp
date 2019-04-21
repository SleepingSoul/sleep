#include "stdafx.h"
#include "Object.h"
#include <Engine/GameTemplate/Game.h>
#include <Engine/Utils/stl_utils.h>

BEGIN_NAMESPACE_SLEEP

Component* Object::addComponent(ComponentsContainer::value_type&& component)
{
    component->setParent(this);
    Component* const handle = component.get();
    m_components.emplace_back(std::move(component));
    return handle;
}

Object* Object::addChild(std::unique_ptr<Object>&& childPtr)
{
    Object* child = childPtr.get();
    m_children.emplace_back(std::move(childPtr));

    if (child->getParent())
    {
        child->detachFromParent();
    }
    child->setParent(this);
    return child;
}

void Object::removeChild(Object* child)
{
    // TODO assert
    auto pred = [child] (std::unique_ptr<Object> const& element)
    {
        return element.get() == child;
    };
    RemoveIf(m_children, pred);
}

void Object::detachFromParent()
{
    if (!m_parent)
    {
        LOG_AND_FAIL_ERROR("parent is null");
        return;
    }

    m_parent->removeChild(this);
    m_parent = nullptr;
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
}

END_NAMESPACE_SLEEP
