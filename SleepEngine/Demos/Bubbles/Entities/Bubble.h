#pragma once

struct BubbleSettings
{
    float Speed = 0.f;
    float FlightDistance = 0.f;
    int WorkCount = 0;
};

class Bubble : public slp::Component
{
    using Base = slp::Component;
public:
    Bubble(BubbleSettings settings);

    void launch(float rotation);
    void update(float dt) override;

private:
    BubbleSettings m_settings;
    glm::vec2 m_startPosition;
};

std::unique_ptr<slp::Object> createBubbleObject(BubbleSettings settings);
