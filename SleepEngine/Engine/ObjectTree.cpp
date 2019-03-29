#include "stdafx.h"
#include "ObjectTree.h"


BeginNamespaceSleep

void ObjectTree::update(float dt)
{
    for (auto& object : m_objects)
    {
        object->update(dt);
    }
}

void ObjectTree::addToRoot(ObjectsContainer::value_type&& object)
{
    m_objects.emplace_back(std::move(object));
}

EndNamespaceSleep
