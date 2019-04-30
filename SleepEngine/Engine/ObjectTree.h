// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

// Entity manager in ECS
class ObjectTree
{
    FORBID_COPY(ObjectTree)
public:
    using ObjectsContainer = std::vector<std::unique_ptr<Object>>;
    using DeleteLaterObjectContainer = std::vector<Object const*>;

    ObjectTree() = default;
    ObjectTree(ObjectTree&&) = default;
    ObjectTree operator=(ObjectTree&& other)
    {
        m_objects = std::move(m_objects);
    }

    void update(float dt);
    void postUpdate();

    void removeLater(Object const* object);
    void removeLater(Object const& object) { removeLater(&object); }

    void addToRoot(std::unique_ptr<Object>&& object);
    void clear();

protected:
    ObjectsContainer m_objects;
    DeleteLaterObjectContainer m_deleteLaterObjects;

private:
    void removeObjects();
};

END_NAMESPACE_SLEEP
