#include "stdafx.h"
#include "ObjectTree.h"


BEGIN_NAMESPACE_SLEEP

void ObjectTree::update(float dt)
{
    for (auto& object : m_objects)
    {
        object->update(dt);
    }

    postUpdate();
}

void ObjectTree::postUpdate()
{
    removeObjects();
}

void ObjectTree::removeLater(Object const* object)
{
    if (!contains(m_deleteLaterObjects, object))
    {
        m_deleteLaterObjects.push_back(object);
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

void ObjectTree::removeObjects()
{
    for (Object const* const objectToRemove : m_deleteLaterObjects)
    {
        auto const isObjectToRemove = [objectToRemove](auto const& object)
        {
            return object.get() == objectToRemove;
        };

        auto const it = std::find_if(C_All(m_objects), isObjectToRemove);

        if (it == m_objects.cend())
        {
            LOG_AND_FAIL("Invalid Object pointer in 'objectsToDelete' container");
            continue;
        }

        m_objects.erase(it);
    }
}

END_NAMESPACE_SLEEP
