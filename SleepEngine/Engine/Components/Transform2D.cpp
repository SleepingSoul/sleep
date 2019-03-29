#include "stdafx.h"
#include "Transform2D.h"


BeginNamespaceSleep

Transform2D::Transform2D() noexcept(true)
    : Base(getTypeID <Transform2D>())
    , scale(1.f, 1.f)
    , position(0.f, 0.f)
    , size(1.f, 1.f)
    , layer(1)
    , rotation(0.f)
{}

EndNamespaceSleep
