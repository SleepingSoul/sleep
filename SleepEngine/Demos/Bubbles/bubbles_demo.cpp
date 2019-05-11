#include "stdafx.h"
#include "bubbles_demo.h"
#include <Demos/Bubbles/Config/BubbleConfig.h>
#include <Demos/Bubbles/Entities/BubbleGun.h>

void initBubbleDemoScene()
{
    slp::globalConfigManager().addConfig<BubbleConfig>();
    slp::globalConfigManager().loadAllConfigs();

    auto bubbleGunObject = createBubbleGunObject();
    auto& transform = slp::getTransform(*bubbleGunObject);
    
    auto* bubbleGun = bubbleGunObject->getComponent<BubbleGun>();
    bubbleGun->setCenterRotation(45.f);
    bubbleGun->startFiring();

    slp::globalEntityManager().addObject(std::move(bubbleGunObject));
}
