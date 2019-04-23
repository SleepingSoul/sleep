#include "stdafx.h"
#include "BubbleGun.h"
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Engine/Utils/math.h>
#include <Engine/object_shortcuts.h>
#include <Demos/Bubbles/Config/BubbleConfig.h>


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
    auto bubble = createBubbleObject(m_settings.BubbleSettings);
    slp::getTransform(*bubble).setRotation(slp::getTransform(m_object).getRotation());
    float const size = globalBubbleConfig().at("bubble_gun").at("bubble").at("size");
    slp::getTransform(*bubble).setSize({size, size});

    auto& ourNode = slp::getHierarchy(m_object);
    ourNode.addChild(std::move(bubble));
}

std::unique_ptr<slp::Object> createBubbleGunObject()
{
    nlohmann::json const& config = globalBubbleConfig().at("bubble_gun");
    auto bubbleGunObject = slp::createGameObject();

    float size = config.at("size");
    slp::getTransform(*bubbleGunObject).setSize({size, size});

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
