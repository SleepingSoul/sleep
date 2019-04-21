#include "stdafx.h"
#include "Component.h"

BEGIN_NAMESPACE_SLEEP

Transform2D& Component::getTransform()
{
    return m_parent->getTransform();
}

Transform2D const& Component::getTransform() const
{
    return m_parent->getTransform();
}

END_NAMESPACE_SLEEP
