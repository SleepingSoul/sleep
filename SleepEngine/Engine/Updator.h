// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Updator
{
public:
    using ContainerType = std::vector <NotOwnedPtr <Updator>>;

    void addChild(Updator* child);
    void addChildren(std::initializer_list <Updator*> children);

    virtual void update();
    virtual void render();
    
private:
    ContainerType m_children;
};

EndNamespaceSleep
