#pragma once
#include <Demos/Bubbles/Entities/Bubble.h>

struct BubbleGunSettings
{
    BubbleSettings BubbleSettings;
    float FireRate = 0.f;
    // how much to the left and right will the gun rotate
    //float FieldOfView = 0.f;
};

// periodically shoots bubbles in set direction,
// with rotating angle left->right->back->repeat
class BubbleGun : public slp::Component
{
    using Base = slp::Component;
public:
    BubbleGun(BubbleGunSettings settings);

    void startFiring();
    void update(float dt) override;

private:
    BubbleGunSettings m_settings;
    slp::Timer m_fireTimer;

    void fireBubble();
};

std::unique_ptr<slp::Object> createBubbleGunObject();
