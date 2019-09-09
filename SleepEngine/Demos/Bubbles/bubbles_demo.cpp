#include "stdafx.h"
#include "bubbles_demo.h"
#include <Engine/object_shortcuts.h>
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Engine/Utils/math.h>
#include <Engine/Utils/unit_utils.h>
#include <Demos/Bubbles/Config/BubbleConfig.h>
#include <Demos/Bubbles/Entities/BubbleGun.h>

void initBubbleDemoScene()
{
    slp::globalConfigManager().addConfig<BubbleConfig>();
    slp::globalConfigManager().loadAllConfigs();

    auto background = slp::createRenderableObject();
    auto* const texture = slp::globalResourceManager().getTexture(slp::Textures::StarBackground);

    background->getComponent<slp::Renderer>()->setTexture(texture);
    slp::globalEntityManager().addObject(std::move(background));

    glm::vec2 const center {0.f, 0.f};
    glm::vec2 const screenHalfSize = slp::screenSizeInWorldCoordinates() / 2.f;

    for (float widthMult : {-1.f, 1.f})
    {
        for (float heightMult : { -1.f, 1.f})
        {
            auto bubbleGunObject = createBubbleGunObject();
            auto* bubbleGun = bubbleGunObject->getComponent<BubbleGun>();

            glm::vec2 const offset = - glm::vec2 { widthMult, heightMult } * slp::getTransform(*bubbleGunObject).getSize().x;

            glm::vec2 const corner = { widthMult * screenHalfSize.x, heightMult * screenHalfSize.y };
            slp::getTransform(*bubbleGunObject).setPosition(corner + offset);
            bubbleGun->setCenterRotation(slp::lookAt(corner, center));
            bubbleGun->startFiring();

            slp::globalEntityManager().addObject(std::move(bubbleGunObject));
        }
    }
}
