#include "stdafx.h"
#include "ObjectTree.h"


BEGIN_NAMESPACE_SLEEP

void ObjectTree::update(float dt)
{
    for (auto& object : m_objects)
    {
        object->update(dt);
    }
}

void ObjectTree::addToRoot(std::unique_ptr<Object>&& object)
{
    m_objects.emplace_back(std::move(object));
}

void ObjectTree::clear()
{
    m_objects.clear();
}

END_NAMESPACE_SLEEP
