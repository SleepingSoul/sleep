// Copyright 2019 Taras Martyniuk
#pragma once
#include <Engine/Config/Loadable.h>

BEGIN_NAMESPACE_SLEEP

// loads and holds some config
// can be stored in config manager, 
class BaseConfig : public Loadable
{
public:
    BaseConfig(TypeID id) : m_typeID(id) {}

    GETTER(getTypeId, m_typeID);

    template <class TComponent>
    static TypeID getConfigTypeID()
    {
        static auto id = m_nextComponentTypeID++;
        return id;
    }

private:
    inline static TypeID m_nextComponentTypeID = 0;
    TypeID m_typeID;
};

END_NAMESPACE_SLEEP
