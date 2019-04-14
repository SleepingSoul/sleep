#pragma once

struct BubbleSettings
{
    float Speed = 0.f;
    glm::vec2 Direction;
};

class Bubble : public slp::Component
{
    using Base = slp::Component;
public:
    Bubble(BubbleSettings settings);

    void update(float dt) override;

private:
    BubbleSettings m_settings
};
