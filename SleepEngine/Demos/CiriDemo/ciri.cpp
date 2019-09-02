#include "stdafx.h"
#include "ciri.h"
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Engine/Utils/unit_utils.h>
#include <Engine/object_shortcuts.h>

void initCiriScene()
{
    auto& game = slp::Game::instance();

    auto background = slp::createRenderableObject();

    auto* const renderer = background->getComponent <slp::Renderer>();
    auto* const transform2D = background->getComponent <slp::Transform2D>();

    renderer->setTexture(game.getResourceManager().getTexture(slp::Textures::Orphea));
    transform2D->setSize(slp::pixelsToMeters(game.getCamera().getScreenSize()));
    transform2D->setLayer(0);

    game.getEntityManager().addObject(std::move(background));

    auto ciriTexture = game.getResourceManager().getTexture(slp::Textures::Cirilla);

    for (int i = 0; i < 200; i++)
    {
        auto ciri = slp::createRenderableObject();

        auto* const renderer = ciri->getComponent <slp::Renderer>();
        auto* const transform2D = ciri->getComponent <slp::Transform2D>();

        renderer->setTexture(ciriTexture);
        transform2D->setLayer(1);
        transform2D->setRotation(static_cast <float>(i) * 4.4f);
        transform2D->setSize(slp::pixelsToMeters(ciriTexture->getSize()));
        transform2D->setPosition({ -slp::pixelsToMeters(game.getCamera().getScreenWidth() / 2.f) + i++ / 20.f, 0.f });
        game.getEntityManager().addObject(std::move(ciri));
    }
}