#include "stdafx.h"
#include "HierarchyNode.h"
#include <Engine/Utils/stl_utils.h>


BEGIN_NAMESPACE_SLEEP

HierarchyNode::HierarchyNode()
    : Base(Component::getComponentTypeID<HierarchyNode>())
{}

Object* HierarchyNode::addChild(std::unique_ptr<Object>&& child)
{
    auto* childNode = child->getComponent<HierarchyNode>();

    if(!childNode)
    {
        childNode = child->addComponent<HierarchyNode>();
    }

    if (childNode->getParent())
    {
        childNode->detachFromParent();
    }
    childNode->setParent(m_object);

    auto* childHandle = child.get();
    m_children.emplace_back(std::move(child));
    return childHandle;
}

void HierarchyNode::removeChild(Object* child)
{
    // TODO assert
    auto pred = [child] (std::unique_ptr<Object> const& element)
    {
        return element.get() == child;
    };
    removeIf(m_children, pred);
}

void HierarchyNode::detachFromParent()
{
    if (!m_object)
    {
        LOG_AND_FAIL("parent is null");
        return;
    }

    auto* parentNode = m_object->getComponent<HierarchyNode>();
    parentNode->removeChild(m_object);
    m_object = nullptr;
}

void HierarchyNode::update(float dt)
{
    Base::update(dt);
    for(auto& childNodeObject : m_children)
    {
        childNodeObject->update(dt);
    }
}
END_NAMESPACE_SLEEP
