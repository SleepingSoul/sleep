#pragma once

BEGIN_NAMESPACE_SLEEP

// allowes object add children, and updates them
class HierarchyNode : public Component
{
public:
	using Base = Component;
	using ChildrenContainer = std::vector<std::unique_ptr<Object>>;

    HierarchyNode();

    GET_SET(Object*, getParent, setParent, m_parent)

    Object* addChild(std::unique_ptr<Object>&& child);
    void removeChild(Object* child);
    void detachFromParent();

    void update(float dt) override;

private:
	void setUpChild(Object& child) const;

    NotOwnedPtr<Object> m_parent;
    ChildrenContainer m_children;
};

COMPONENT_SHORTCUTS(HierarchyNode, getHierarchy)

END_NAMESPACE_SLEEP