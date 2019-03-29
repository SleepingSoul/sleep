// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Component
{
    ForbidCopyAndMove(Component)
public:
    Component(TypeID id)
        : m_typeID(id)
    {}

    virtual void update(float dt) = 0;
    virtual void setParent(Object* parent) { m_parent = parent; }
    TypeID getComponentTypeID() const { return m_typeID; }

protected:
    NotOwnedPtr <Object> m_parent{ nullptr };

private:
    TypeID m_typeID;
};

EndNamespaceSleep
