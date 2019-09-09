#include "stdafx.h"
#include "BubbleGun.h"
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Engine/Utils/math.h>
#include <Engine/object_shortcuts.h>
#include <Demos/Bubbles/Config/BubbleConfig.h>


BubbleGun::BubbleGun(BubbleGunSettings settings)
    :  Base(getComponentTypeID <BubbleGun>())
    , m_settings(settings)
{
    LOG_AND_ASSERT_ERROR(settings.FieldOfView > 0.f, "field of view must be > 0");
    LOG_AND_ASSERT_ERROR(settings.FireRate > 0.f, "fire rate must be > 0");
    LOG_AND_ASSERT_ERROR(settings.RotationSpeed > 0.f, "RotationSpeed must be > 0");
}

void BubbleGun::setCenterRotation(float centerRotation)
{
    slp::getTransform(m_object).setRotation(centerRotation);
    m_centerRotation = centerRotation;
    float const leftBound = centerRotation + m_settings.FieldOfView;
    float const rightBound = centerRotation - m_settings.FieldOfView;
    m_startRotation = leftBound;
    m_finishRotation = rightBound;
    m_rotationCycleTime = std::abs(m_finishRotation - m_startRotation) / m_settings.RotationSpeed;
    // middle
    m_rotationAccumulator = m_rotationCycleTime / 2;
}

void BubbleGun::startFiring()
{
    m_fireTimer.every(m_settings.FireRate, [this] 
    { 
        int const maxCount = globalBubbleConfig().at("bubble_gun").at("max_bubbles");
        int const bubblesFired = slp::getHierarchy(m_object).getChildCount();
        if (bubblesFired >= maxCount)
        {
            m_fireTimer.stop();
            return;
        }

        fireBubble(); 
    });
}

void BubbleGun::update(float dt)
{
    LOG_AND_ASSERT_ERROR(m_rotationAccumulator >= 0.f && m_rotationAccumulator <= m_rotationCycleTime, "accumulator out of bounds");

    Base::update(dt);
    m_rotationAccumulator += dt;

    float const lerpTime = m_rotationAccumulator / m_rotationCycleTime;
    float const rotated = slp::lerp(m_startRotation, m_finishRotation, lerpTime);
    slp::getTransform(m_object).setRotation(rotated);

    if (lerpTime >= 1.0f)
    {
        // start rotating in opposite dir
        m_rotationAccumulator = 0.f;
        std::swap(m_startRotation, m_finishRotation);
    }
}

void BubbleGun::fireBubble()
{
    auto bubble = createBubbleObject(m_settings.BubbleSettings);

    bubble->getComponent<Bubble>()->launch(slp::getTransform(m_object).getRotation());
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

    auto& bubbleConfig = config.at("bubble");
    BubbleGunSettings const settings
    {
        {
            bubbleConfig.at("speed"),
            bubbleConfig.at("flight_distance"),
            bubbleConfig.at("work_count")
        },
        config.at("fire_rate"),
        config.at("field_of_view"),
        config.at("rotation_speed")
    };
    bubbleGunObject->addComponent(std::make_unique<BubbleGun>(settings));
    auto* const renderer = bubbleGunObject->addComponent<slp::Renderer>();

    auto& game = slp::Game::instance();

    renderer->setTexture(slp::globalResourceManager().getTexture(slp::Textures::spaceship));
    
    return bubbleGunObject;
}
