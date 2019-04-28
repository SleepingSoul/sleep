#include "stdafx.h"
#include "HierarchyNode.h"
#include <Engine/Utils/stl_utils.h>


BEGIN_NAMESPACE_SLEEP

HierarchyNode::HierarchyNode()
    : Base(Component::getComponentTypeID<HierarchyNode>())
    , m_parent(nullptr)
{}

Object* HierarchyNode::addChild(std::unique_ptr<Object>&& child)
{
    auto* const childHandle = child.get();

    setUpChild(*childHandle);

    m_children.emplace_back(std::move(child));
    return childHandle;
}

void HierarchyNode::removeChild(Object* child)
{
    auto const isChildToDelete = [child] (std::unique_ptr<Object> const& element)
    {
        return element.get() == child;
    };

    auto const childToDelete = findIf(m_children, isChildToDelete);

    if (childToDelete != m_children.cend())
    {
        LOG_AND_FAIL("'removeChild' called for object that is not out child");
        return;
    }

    m_children.erase(childToDelete);
}

void HierarchyNode::detachFromParent()
{
    if (!m_parent)
    {
        LOG_AND_FAIL("parent is null");
        return;
    }

    auto* const parentNode = m_parent->getComponent<HierarchyNode>();
    parentNode->removeChild(m_parent);
    m_parent = nullptr;
}

void HierarchyNode::update(float dt)
{
    Base::update(dt);

    for (auto& childNodeObject : m_children)
    {
        childNodeObject->update(dt);
    }
}

void HierarchyNode::setUpChild(Object& child) const
{
    auto* childNode = child.getComponent<HierarchyNode>();

    if (!childNode)
    {
        childNode = child.addComponent<HierarchyNode>();
    }

    if (childNode->getParent())
    {
        childNode->detachFromParent();
    }

    childNode->setParent(m_object);
}

END_NAMESPACE_SLEEP
