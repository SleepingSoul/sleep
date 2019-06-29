#include "stdafx.h"
#include "EntityManager.h"

BEGIN_NAMESPACE_SLEEP

EntityManager::~EntityManager()
{
    m_clearAll = true;
    removeObjects();
}

void EntityManager::addObject(std::unique_ptr<Object>&& object, bool shouldUpdate)
{
    m_addLaterObjects.emplace_back(std::move(object), shouldUpdate);
}

void EntityManager::removeObjectLater(Object const* object)
{
    if (!contains(m_removeLaterObjects, object))
    {
        m_removeLaterObjects.push_back(object);
    }
}

void EntityManager::clearLater()
{
    m_clearAll = true;
}

void EntityManager::update(float dt)
{
    for (auto* const object : m_objectsToUpdate)
    {
        object->update(dt);
    }

    postUpdate();
}

void EntityManager::postUpdate()
{
    addObjects();
    removeObjects();
}

void EntityManager::addObjects()
{
    for (auto&& [object, shouldUpdate] : m_addLaterObjects)
    {
        if (shouldUpdate)
        {
            m_objectsToUpdate.push_back(object.get());
        }

        m_objects.emplace_back(std::move(object));
    }

    m_addLaterObjects.clear();
}

void EntityManager::removeObjects()
{
    // more effective implementation in case of full cleanup
    if (m_clearAll)
    {
        m_clearAll = false;
        m_objects.clear();
        m_removeLaterObjects.clear();
        m_addLaterObjects.clear();
        m_objectsToUpdate.clear();
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
            continue;
        }

        m_objects.erase(it);
    }

    m_removeLaterObjects.clear();
}

END_NAMESPACE_SLEEP
