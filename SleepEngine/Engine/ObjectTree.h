// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class ObjectTree
{
public:
    using ObjectsContainer = std::vector <std::unique_ptr <Object>>;

    void update(float dt);
    void addToRoot(ObjectsContainer::value_type&& object);

protected:
    ObjectsContainer m_objects;
};

END_NAMESPACE_SLEEP
