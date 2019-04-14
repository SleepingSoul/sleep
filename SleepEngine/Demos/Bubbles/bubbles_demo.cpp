#include "stdafx.h"
#include "bubbles_demo.h"
#include <Demos/Bubbles/Entities/BubbleGun.h>

void initScene(slp::Game::Scene & scene)
{
    std::unique_ptr<slp::Object> bubbleGun = createBubbleGunObject();
    bubbleGun->getTransform().getData().setPosition({ 0.f, 0.f });

    scene.addToRoot(std::move(bubbleGun));
}
