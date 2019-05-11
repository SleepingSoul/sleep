// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Object
{
public:
    using ComponentsContainer = std::vector <std::unique_ptr <Component>>;

    void update(float dt);

    Component* addComponent(ComponentsContainer::value_type&& component);

    template <class TComponent, class ...Args>
    TComponent* addComponent(Args&&... constructorArgs)
    {
        static_assert(std::is_base_of_v <Component, TComponent>, "TComponent should be a heir of slp::Component class!");
        auto* const addedComponent = addComponent(std::make_unique <TComponent>(std::forward <Args>(constructorArgs)...));
        return static_cast<TComponent*>(addedComponent);
    }
    
    template <class TComponent>
    TComponent const* getComponent() const
    {
        auto const id = Component::getComponentTypeID <TComponent>();

        auto const findByID = [id](auto const& component)
        {
            return component->getComponentTypeID() == id;
        };

        auto it = std::find_if(m_components.cbegin(), m_components.cend(), findByID);
        
        if (it == m_components.cend())
        {
            return nullptr;
        }

        return static_cast <TComponent*>(it->get());
    }

    template <class TComponent>
    TComponent* getComponent()
    {
        return const_cast <TComponent*>(static_cast <Object const*>(this)->getComponent <TComponent>());
    }

    void removeLater() const;

protected:
    ComponentsContainer m_components;
};

END_NAMESPACE_SLEEP
