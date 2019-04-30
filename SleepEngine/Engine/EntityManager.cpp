#include "stdafx.h"
#include "EntityManager.h"

BEGIN_NAMESPACE_SLEEP

void EntityManager::addObject(std::unique_ptr<Object>&& object)
{
    m_objects.emplace_back(std::move(object));
}

void EntityManager::removeObjectLater(Object const* object)
{
    if (!contains(m_removeLaterObjects, object))
    {
        m_removeLaterObjects.push_back(object);
    }
}

void EntityManager::clear()
{
    m_clearAll = true;
}

void EntityManager::update(float dt)
{
    for (auto& object : m_objects)
    {
        object->update(dt);
    }

    postUpdate();
}

void EntityManager::postUpdate()
{
    // more effective implementation in case of full cleanup
    if (m_clearAll)
    {
        m_clearAll = false;
        m_objects.clear();
        m_removeLaterObjects.clear();
        return;
    }

    for (auto const* const objectToRemove : m_removeLaterObjects)
    {
        auto const isObjectToRemove = [objectToRemove](auto const& object)
        {
            return objectToRemove == object.get();
        };

        auto const[found, it] = findIf(m_objects, isObjectToRemove);

        if (!found)
        {
            LOG_AND_FAIL("EntityManager error: invalid Object pointer.");
            return;
        }

        m_objects.erase(it);
    }

    m_removeLaterObjects.clear();
}

END_NAMESPACE_SLEEP
