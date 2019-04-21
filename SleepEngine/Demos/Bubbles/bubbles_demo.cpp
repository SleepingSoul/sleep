#include "stdafx.h"
#include "bubbles_demo.h"
#include <Demos/Bubbles/Config/BubbleConfig.h>
#include <Demos/Bubbles/Entities/BubbleGun.h>

void initBubbleDemoScene(slp::Game::Scene& scene)
{
    slp::globalConfigManager().addConfig<BubbleConfig>();
    slp::globalConfigManager().loadAllConfigs();




    auto bubbleGun = createBubbleGunObject();
    auto& transform = bubbleGun->getTransform().getData();
    transform.setPosition({ 0.f, 0.f });\
    transform.setRotation(45.f);

    scene.addToRoot(std::move(bubbleGun));
}
