#include "stdafx.h"
#include "EntityManager.h"

BEGIN_NAMESPACE_SLEEP

void EntityManager::addObject(std::unique_ptr<Object>&& object)
{
    m_objects.emplace_back(std::move(object));
}

void EntityManager::removeObject(Object const* objectToRemove)
{
    auto const isObjectToRemove = [objectToRemove](auto const& object)
    {
        return objectToRemove == object.get();
    };

    auto const[found, it] = findIf(m_objects, isObjectToRemove);

    if (!found)
    {
        LOG_AND_FAIL("EntityManager error: 'removeObject' called with invalid Object pointer.");
        return;
    }

    m_objects.erase(it);
}

void EntityManager::update(float dt)
{
    for (auto& object : m_objects)
    {
        object->update(dt);
    }
}

END_NAMESPACE_SLEEP
