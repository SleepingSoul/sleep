#include "stdafx.h"
#include "HierarchyNode.h"
#include <Engine/Utils/stl_utils.h>


BEGIN_NAMESPACE_SLEEP

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
        LOG_AND_FAIL_ERROR("parent is null");
        return;
    }

    m_object->removeChild(this);
    m_object = nullptr;
}

END_NAMESPACE_SLEEP
