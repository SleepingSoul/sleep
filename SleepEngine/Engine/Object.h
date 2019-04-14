// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Object
{
public:
    using ComponentsContainer = std::vector <std::unique_ptr <Component>>;

    virtual void update(float dt);

    void addComponent(ComponentsContainer::value_type&& component);

    template <class TComponent>
    void addComponent()
    {
        static_assert(std::is_default_constructible_v <TComponent>, "TComponent is not default constructible. Please, "
            "create an instance of this class and use non-templated 'addComponent' method.");
        addComponent(std::make_unique <TComponent>());
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

protected:
    ComponentsContainer m_components;
};

END_NAMESPACE_SLEEP
