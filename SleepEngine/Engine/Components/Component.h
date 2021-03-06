// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Transform2D;
class Object;

class Component
{
    FORBID_COPY_AND_MOVE(Component)
public:
    Component(TypeID id)
        : m_typeID(id)
    {}
    virtual ~Component() {}

    virtual void update(float dt) {}

    GETTER(getObject, m_object)
    void setParent(Object* parent) 
    { 
        m_object = parent; 
        onAddedToObject();
    }

    TypeID getComponentTypeID() const { return m_typeID; }

    template <class TComponent>
    static TypeID getComponentTypeID()
    {
        static auto id = m_nextComponentTypeID++;
        return id;
    }

protected:
    NotOwnedPtr <Object> m_object{ nullptr };

    virtual void onAddedToObject() {}

private:
    TypeID m_typeID;

    inline static TypeID m_nextComponentTypeID = 0;
};

END_NAMESPACE_SLEEP
