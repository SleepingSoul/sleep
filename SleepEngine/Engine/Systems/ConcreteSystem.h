// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

template <class TComponent>
class ConcreteSystem : public ISystem
{
    FORBID_COPY_AND_MOVE(ConcreteSystem)
public:
    using ComponentsContainer = std::vector <NotOwnedPtr <TComponent>>;

    ConcreteSystem() = default;

    void enter(Component* component) override
    {
        m_components.push_back(static_cast <TComponent*>(component));
    }

    void exit(Component* component) override
    {
        auto it = std::find(m_components.cbegin(), m_components.cend(), component);
        
        if (it == m_components.cend())
        {
            LOG_AND_ASSERT_ERROR(false, "Attempt to exit from component that is not a part of this system.");
            return;
        }

        m_components.erase(it);
    }

private:
    ComponentsContainer m_components;
};

END_NAMESPACE_SLEEP
