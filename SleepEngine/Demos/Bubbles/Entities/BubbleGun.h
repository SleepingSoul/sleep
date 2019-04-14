#pragma once

struct BubbleGunSettings
{
    glm::vec2 ShootDirection;
    // how much to the left and right will the gun rotate
    float AngleDifference = 0.f;
};

// periodically shoots bubbles in set direction,
// with rotating angle left->right->back->repeat
class BubbleGun : public slp::Object
{
public:
    BubbleGun(BubbleGunSettings settings);
};
