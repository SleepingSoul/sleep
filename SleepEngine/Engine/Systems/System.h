// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Component;

// System shouldn't have state, it should have a logic

class ISystem
{
public:
    virtual void update(float dt) = 0;
    virtual void enter(Component* component) = 0;
    virtual void exit(Component* component) = 0;
};

END_NAMESPACE_SLEEP
