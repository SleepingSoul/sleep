#pragma once

class Bubble : public slp::Component
{
    using Base = slp::Component;
public:
    Bubble(float speed);

    void launch(glm::vec2 direction);
    void update(float dt) override;

private:
    float m_speed;
};

std::unique_ptr<slp::Object> createBubbleObject(float speed);
