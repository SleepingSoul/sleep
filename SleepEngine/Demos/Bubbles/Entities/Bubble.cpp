#include "stdafx.h"
#include "Bubble.h"

Bubble::Bubble(BubbleSettings settings)
    : Base(getComponentTypeID <Bubble>())
    , m_settings(settings)
{}

void Bubble::update(float dt)
{
    auto* transform = m_parent->getComponent<slp::Transform2D>();
    transform->translate(m_settings.Direction * m_settings.Speed);
}
