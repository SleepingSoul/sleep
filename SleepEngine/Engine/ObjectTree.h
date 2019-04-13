// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class ObjectTree
{
    FORBID_COPY(ObjectTree)
public:
    using ObjectsContainer = std::vector <std::unique_ptr <Object>>;

    ObjectTree() = default;
    ObjectTree(ObjectTree&&) = default;
    ObjectTree operator=(ObjectTree&& other)
    {
        m_objects = std::move(m_objects);
    }

    void update(float dt);
    void addToRoot(ObjectsContainer::value_type&& object);
    void clear();

protected:
    ObjectsContainer m_objects;
};

END_NAMESPACE_SLEEP
