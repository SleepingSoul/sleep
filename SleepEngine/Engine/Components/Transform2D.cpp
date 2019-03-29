#include "stdafx.h"
#include "Transform2D.h"


BeginNamespaceSleep

Transform2D::Transform2D() noexcept(true)
    : Base(getTypeID <Transform2D>())
    , m_data{
        { 1.f, 1.f },
        { 0.f, 0.f },
        { 1.f, 1.f },
        1,
        0.f
      }
{}

EndNamespaceSleep
