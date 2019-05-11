// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class EntityManager
{
    FORBID_COPY_AND_MOVE(EntityManager)
public:
    EntityManager() = default;

    void addObject(std::unique_ptr <Object>&& object, bool shouldUpdate = true);
    void removeObjectLater(Object const* object);
    void clear();

    void update(float dt);

private:
    void postUpdate();

    void addObjects();
    void removeObjects();

    std::vector<std::unique_ptr<Object>> m_objects;
    std::vector<Object*> m_objectsToUpdate;
    std::vector<Object const*> m_removeLaterObjects;
    std::vector<std::pair<std::unique_ptr<Object>, bool>> m_addLaterObjects;

    bool m_clearAll{ false };
};

END_NAMESPACE_SLEEP
