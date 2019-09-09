#pragma once

BEGIN_NAMESPACE_SLEEP

// allowes object add children, and updates them
class HierarchyNode : public Component
{
public:
    using Base = Component;
    using ChildrenContainer = std::vector<NotOwnedPtr<Object>>;

    HierarchyNode();
    ~HierarchyNode() override;

    GET_SET(Object*, getParent, setParent, m_parent)
    size_t getChildCount() const { return m_children.size(); }

    Object* addChild(std::unique_ptr<Object>&& child);
    void removeChild(Object const* child);
    void removeAllChildren();
    void detachFromParent();

    void update(float dt) override;

private:
    Object* addChild(Object* child);

    NotOwnedPtr<Object> m_parent{ nullptr };
    ChildrenContainer m_children;
};

COMPONENT_SHORTCUTS(HierarchyNode, getHierarchy)

END_NAMESPACE_SLEEP
