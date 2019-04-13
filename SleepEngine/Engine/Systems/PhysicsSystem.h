// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class PhysicsSystem : public ConcreteSystem <RigidBody>
{
    FORBID_COPY_AND_MOVE(PhysicsSystem)
public:
    PhysicsSystem();

    void update(float dt) override;
};

END_NAMESPACE_SLEEP
