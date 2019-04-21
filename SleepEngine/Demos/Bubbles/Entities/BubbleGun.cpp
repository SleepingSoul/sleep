#include "stdafx.h"
#include "BubbleGun.h"
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Demos/Bubbles/Config/BubbleConfig.h>
#include <Engine/Utils/math.h>

BubbleGun::BubbleGun(BubbleGunSettings settings)
    :  Base(getComponentTypeID <BubbleGun>())
    , m_settings(settings)
{}

void BubbleGun::startFiring()
{
    m_fireTimer.every(m_settings.FireRate, [this] { fireBubble(); } );
}

void BubbleGun::update(float dt)
{
    Base::update(dt);
}

void BubbleGun::fireBubble()
{
    float const rotation = slp::getTransform(m_object).getRotation();
    glm::vec2 lookDir = slp::directionFromRotation(rotation);

    auto bubble = createBubbleObject(m_settings.BubbleSettings);
    slp::getTransform(m_object).setRotation(rotation);
    float const size = globalBubbleConfig().at("bubble_gun").at("bubble").at("size");
    slp::getTransform(*bubble).setSize({size, size});

    m_object->addChild(std::move(bubble));
}

std::unique_ptr<slp::Object> createBubbleGunObject()
{
    nlohmann::json const& config = globalBubbleConfig().at("bubble_gun");
    auto bubbleGunObject = std::make_unique<slp::Object>();

    float size = config.at("size");
    bubbleGunObject->getTransform().setSize({size, size});

    BubbleGunSettings const settings
    {
        {
            config.at("bubble").at("speed"),
            config.at("bubble").at("flight_distance"),
        },
        config.at("fire_rate")
    };
    bubbleGunObject->addComponent(std::make_unique<BubbleGun>(settings));
    auto* const renderer = bubbleGunObject->addComponent<slp::Renderer>();

    auto& game = slp::Game::instance();

    renderer->setTexture(slp::globalResourcemanager().getTexture(slp::Textures::Spaceship));
    
    return bubbleGunObject;
}
