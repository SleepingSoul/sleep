// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class EntityManager
{
    FORBID_COPY_AND_MOVE(EntityManager)
public:
    using EntitiesContainer = std::vector<std::unique_ptr<Object>>;
    using EntitiesToRemoveContainer = std::vector<Object const*>;

    EntityManager() = default;

    void addObject(std::unique_ptr <Object>&& object);
    void removeObjectLater(Object const* object);
    void clear();

    void update(float dt);

private:
    void postUpdate();

    EntitiesContainer m_objects;
    EntitiesToRemoveContainer m_removeLaterObjects;

    bool m_clearAll{ false };
};

END_NAMESPACE_SLEEP
