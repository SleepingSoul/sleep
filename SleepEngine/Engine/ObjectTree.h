// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class ObjectTree
{
public:
    using ObjectsContainer = std::vector <std::unique_ptr <Object>>;

    void update(float dt);
    void addToRoot(ObjectsContainer::value_type&& object);

protected:
    ObjectsContainer m_objects;
};

EndNamespaceSleep
