#include "stdafx.h"
#include "BubbleGun.h"
#include <Engine/ResourceManagement/ResourceManager.h>

BubbleGun::BubbleGun(BubbleGunSettings settings)
    :  Base(getComponentTypeID <BubbleGun>())
    , m_settings(settings)
{}

void BubbleGun::update(float dt)
{
}

slp::Object* CreateBubbleGunObject()
{
    auto* bubbleGunObject = new slp::Object();

    BubbleGunSettings const settings
    {
        {0.f, 1.f},
        1.f
    };
    bubbleGunObject->addComponent(std::make_unique<BubbleGun>(settings));
    auto* const renderer = bubbleGunObject->addComponent<slp::Renderer>();

    auto& game = slp::Game::instance();

    renderer->setTexture(game.getResourceManager().getTexture(slp::Textures::Spaceship));
    
    return bubbleGunObject;
}
