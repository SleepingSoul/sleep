// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class EntityManager
{
    FORBID_COPY_AND_MOVE(EntityManager)
public:
    using EntitiesContainer = std::vector<std::unique_ptr<Object>>;

    EntityManager() = default;

    void addObject(std::unique_ptr <Object>&& object);
    void removeObject(Object const* object);
    void clear();

    void update(float dt);

private:
    EntitiesContainer m_objects;
};

END_NAMESPACE_SLEEP
