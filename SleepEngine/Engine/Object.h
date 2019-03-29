// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Object
{
public:
    using ComponentsContainer = std::vector <std::unique_ptr <Component>>;

    void addComponent(ComponentsContainer::value_type&& component);

    virtual void update(float dt);
    
    template <class TComponent>
    TComponent const* getComponent() const
    {
        auto const id = getTypeID <TComponent>();
        auto const findByID = [id](ComponentsContainer::reference component)
        {
            return component->getComponentTypeID() == id;
        }
        auto it = std::find(m_components.cbegin(), m_components.cend(), findByID);
        
        if (it == m_components.end())
        {
            return nullptr;
        }

        return it->get();
    }

    template <class TComponent>
    TComponent* getComponent()
    {
        return const_cast <TComponent*>(const_cast <Object const*>(this)->getComponent <TComponent>());
    }

protected:
    ComponentsContainer m_components;
};

EndNamespaceSleep
