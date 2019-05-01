#include "stdafx.h"
#include "HierarchyNode.h"
#include <Engine/Utils/stl_utils.h>


BEGIN_NAMESPACE_SLEEP

HierarchyNode::HierarchyNode()
    : Base(Component::getComponentTypeID<HierarchyNode>())
{}

HierarchyNode::~HierarchyNode()
{
    // in ECS, there will be some 'reset' function instead. Now we have no pool
    removeAllChildren();

    if (m_parent)
    {
        detachFromParent();
    }
}

Object* HierarchyNode::addChild(std::unique_ptr<Object>&& child)
{
    auto* const addedChild = child.get();
    globalEntityManager().addObject(std::move(child), false);
    return addChild(addedChild);
}

Object* HierarchyNode::addChild(Object* child)
{
    auto* childNode = child->getComponent<HierarchyNode>();

    if (!childNode)
    {
        childNode = child->addComponent<HierarchyNode>();
    }

    if (childNode->getParent())
    {
        childNode->detachFromParent();
    }

    childNode->setParent(m_object);

    m_children.emplace_back(child);
    return child;
}

void HierarchyNode::removeChild(Object const* child)
{
    auto const [found, it] = find(m_children, child);

    if (!found)
    {
        LOG_AND_FAIL("'removeChild' called for object that is not our child");
        return;
    }

    m_children.erase(it);
}

void HierarchyNode::removeAllChildren()
{
    for (auto* const child : m_children)
    {
        slp::getHierarchy(*child).setParent(nullptr);
        globalEntityManager().removeObjectLater(child);
    }

    m_children.clear();
}

void HierarchyNode::detachFromParent()
{
    if (!m_parent)
    {
        LOG_AND_FAIL("parent is null");
        return;
    }

    auto* const parentNode = m_parent->getComponent<HierarchyNode>();
    parentNode->removeChild(m_object);
    m_parent = nullptr;
}

void HierarchyNode::update(float dt)
{
    for (auto* const child : m_children)
    {
        child->update(dt);
    }
}

END_NAMESPACE_SLEEP
