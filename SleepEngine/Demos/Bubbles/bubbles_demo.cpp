#include "stdafx.h"
#include "bubbles_demo.h"
#include <Demos/Bubbles/Config/BubbleConfig.h>
#include <Demos/Bubbles/Entities/BubbleGun.h>

void initBubbleDemoScene(slp::Game::Scene& scene)
{
    slp::globalConfigManager().addConfig<BubbleConfig>();
    slp::globalConfigManager().loadAllConfigs();

    auto bubbleGunObject = createBubbleGunObject();
    auto& transform = slp::getTransform(*bubbleGunObject);
    
    auto* bubbleGun = bubbleGunObject->getComponent<BubbleGun>();
    bubbleGun->setCenterRotation(45.f);
    bubbleGun->startFiring();

    scene.addToRoot(std::move(bubbleGunObject));
}
