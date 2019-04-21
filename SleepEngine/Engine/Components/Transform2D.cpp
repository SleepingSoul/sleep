#include "stdafx.h"
#include "transform2D.h"


BEGIN_NAMESPACE_SLEEP

Transform2D::Transform2D() noexcept(true)
    : Base(getComponentTypeID <Transform2D>())
{}

void Transform2D::translate(glm::vec2 translation)
{
    setPosition(getPosition() + translation);
}

void Transform2D::rotate(float rotation)
{
    setRotation(getRotation() + rotation);
}

END_NAMESPACE_SLEEP
