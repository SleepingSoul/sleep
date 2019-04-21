#pragma once

BEGIN_NAMESPACE_SLEEP

// allowes object add children, and updates them
class HierarchyNode : public Component
{
    using Base = Component;
public:
    GET_SET(Object*, getParent, setParent, m_object)

    Object* addChild(std::unique_ptr<Object>&& child);
    void removeChild(Object* child);
    void detachFromParent();

    void update(float dt) override;

private:
    NotOwnedPtr<Object> m_object = nullptr;
    std::vector<std::unique_ptr<Object>> m_children;
};

COMPONENT_SHORTCUTS(HierarchyNode, getHierarchy)

END_NAMESPACE_SLEEP