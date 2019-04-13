#include "stdafx.h"
#include "Transform2D.h"


BEGIN_NAMESPACE_SLEEP

Transform2D::Transform2D() noexcept(true)
    : Base(getComponentTypeID <Transform2D>())
{}

END_NAMESPACE_SLEEP
