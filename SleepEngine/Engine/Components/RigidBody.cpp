#include "stdafx.h"
#include "RigidBody.h"


BEGIN_NAMESPACE_SLEEP

RigidBody::RigidBody() noexcept(true)
    : Base(getComponentTypeID <RigidBody>())
    , m_size(0.f, 0.f)
    , m_velocity(0.f, 0.f)
    , m_mass(1.f)
{}

END_NAMESPACE_SLEEP
