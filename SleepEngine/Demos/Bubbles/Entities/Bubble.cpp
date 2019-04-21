#include "stdafx.h"
#include "Bubble.h"
#include <Engine/Utils/math.h>

Bubble::Bubble(float speed)
    : Base(getComponentTypeID <Bubble>())
    , m_speed(speed)
{}

void Bubble::launch(glm::vec2 direction)
{
    //getTransform().setRotation()
}

void Bubble::update(float dt)
{
    glm::vec2 direction = slp::directionFromRotation(getTransform().getData().getRotation());
    getTransform().translate(direction * m_speed * dt);
}

std::unique_ptr<slp::Object> createBubbleObject(float speed)
{
    return std::unique_ptr<slp::Object>();
}
