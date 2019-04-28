#include "stdafx.h"
#include "Bubble.h"
#include <Engine/Utils/math.h>
#include <Engine/object_shortcuts.h>
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Demos/Bubbles/dummy_work.h>

Bubble::Bubble(BubbleSettings settings)
    : Base(getComponentTypeID <Bubble>())
    , m_settings(settings)
{}

void Bubble::launch(float rotation)
{
    slp::getTransform(m_object).setRotation(rotation);
    m_startPosition = slp::getTransform(m_object).getPosition();
}

void Bubble::update(float dt)
{
    auto& transform = slp::getTransform(m_object);

    float const distanceFlown = static_cast <float>((transform.getPosition() - m_startPosition).length());
    if (distanceFlown >= m_settings.FlightDistance)
    {
        // TODO: destroy object
    }

    glm::vec2 const direction = slp::directionFromRotation(transform.getRotation());
    transform.translate(direction * m_settings.Speed * dt);

    for (int i = 0; i < m_settings.WorkCount; i++)
    {
        DummyCounter++;
    }

    Base::update(dt);
}

std::unique_ptr<slp::Object> createBubbleObject(BubbleSettings settings)
{
    auto bubble = slp::createGameObject();
    bubble->addComponent<Bubble>(settings);
    auto* const renderer = bubble->addComponent<slp::Renderer>();
    renderer->setTexture(slp::globalResourceManager().getTexture(slp::Textures::BubbleSimple));
    return bubble;
}
