// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Component
{
    ForbidCopyAndMove(Component)
public:
    virtual void update(float dt) = 0;
    virtual void setParent(Object* parent) { m_parent = parent; }

private:
    NotOwnedPtr <Object> m_parent{ nullptr };
};

EndNamespaceSleep
