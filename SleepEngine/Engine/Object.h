// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

// has Transform2D by default
class Object
{
public:
    using ComponentsContainer = std::vector <std::unique_ptr <Component>>;

    Object();

    GET_SET(Object*, getParent, setParent, m_parent)

    void update(float dt);

    Component* addComponent(ComponentsContainer::value_type&& component);

    template <class TComponent>
    TComponent* addComponent()
    {
        static_assert(std::is_default_constructible_v <TComponent>, "TComponent is not default constructible. Please, "
            "create an instance of this class and use non-templated 'addComponent' method.");
        Component* handle = addComponent(std::make_unique <TComponent>());
        return static_cast<TComponent*>(handle);
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

    Transform2D& getTransform();
    Transform2D const& getTransform() const;

protected:

    ComponentsContainer m_components;
};

END_NAMESPACE_SLEEP
