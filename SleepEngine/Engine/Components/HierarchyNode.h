#pragma once

BEGIN_NAMESPACE_SLEEP

// allowes object add children, and updates them
class HierarchyNode : public Component
{
public:
    GET_SET(Object*, getParent, setParent, m_parent)

    Object* addChild(std::unique_ptr<Object>&& child);
    void removeChild(Object* child);
    void detachFromParent();

private:
    NotOwnedPtr<Object> m_parent = nullptr;
    std::vector<std::unique_ptr<Object>> m_children;
};

END_NAMESPACE_SLEEP