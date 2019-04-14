#include "stdafx.h"
#include "Transform2D.h"


BEGIN_NAMESPACE_SLEEP

Transform2D::Transform2D() noexcept(true)
    : Base(getComponentTypeID <Transform2D>())
{}

void Transform2D::translate(glm::vec2 translation)
{
    m_data.setPosition(m_data.getPosition() + translation);
}

void Transform2D::rotate(float rotation)
{
    // TODO: do smth smarter
    m_data.setRotation(m_data.getRotation() + rotation);
}

END_NAMESPACE_SLEEP
