#include "stdafx.h"
#include "Bubble.h"
#include <Engine/Utils/math.h>
#include <Engine/ResourceManagement/ResourceManager.h>

Bubble::Bubble(BubbleSettings settings)
    : Base(getComponentTypeID <Bubble>())
    , m_settings(settings)
{}

void Bubble::launch(glm::vec2 direction)
{
    m_startPosition = getTransform().getPosition();
}

void Bubble::update(float dt)
{
    float const distanceFlown = (getTransform().getPosition() - m_startPosition).length();
    if (distanceFlown >= m_settings.FlightDistance)
    {
        // TODO: destroy object
    }

    glm::vec2 const direction = slp::directionFromRotation(getTransform().getRotation());
    getTransform().translate(direction * m_settings.Speed * dt);
    Base::update(dt);
}

std::unique_ptr<slp::Object> createBubbleObject(BubbleSettings settings)
{
    auto bubble = std::make_unique<slp::Object>();
    bubble->addComponent(std::make_unique<Bubble>(settings));
    auto* renderer = bubble->addComponent<slp::Renderer>();
    renderer->setTexture(slp::globalResourcemanager().getTexture(slp::Textures::BubbleSimple));
    return bubble;
}
