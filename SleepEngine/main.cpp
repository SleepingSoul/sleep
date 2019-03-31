#include <stdafx.h>
#include <Engine/Generated/all_images.hpp>
#include <Engine/ResourceManagement/ResourceManager.h>

// settings
namespace
{
	size_t const WindowWidth = 1920;
	size_t const WindowHeight = 1080;
}

int main()
{
    EASY_PROFILER_ENABLE;

	slp::Game game(WindowWidth, WindowHeight);

    game.getClock().setFPS(60.f);
	game.getClock().setRestrictFPS(true);

    auto initMainScene = [](slp::Game::Scene& scene)
    {
        auto& game = slp::Game::instance();

        auto background = slp::createRenderableObject();

        auto* const renderer = background->getComponent <slp::Renderer>();
        auto* const transform2D = background->getComponent <slp::Transform2D>();

        renderer->setTexture(game.getResourceManager().getTexture(slp::Textures::Orphea));
        transform2D->getData().setSize(slp::pixelsToMeters(game.getCamera().getScreenSize()));
        transform2D->getData().setLayer(0);

        scene.addToRoot(std::move(background));

        auto ciriTexture = game.getResourceManager().getTexture(slp::Textures::Cirilla);

        for (int i = 0; i < 200; i++)
        {
            auto ciri = slp::createRenderableObject();

            auto* const renderer = ciri->getComponent <slp::Renderer>();
            auto* const transform2D = ciri->getComponent <slp::Transform2D>();

            renderer->setTexture(ciriTexture);
            auto& transformData = transform2D->getData();
            transformData.setLayer(1);
            transformData.setRotation(static_cast <float>(i) * 4.4f);
            transformData.setSize(slp::pixelsToMeters(ciriTexture->getSize()));
            transformData.setPosition({ -slp::pixelsToMeters(game.getCamera().getScreenWidth() / 2.f) + i++ / 20.f, 0.f });
            scene.addToRoot(std::move(ciri));
        }
    };

    game.getResourceManager().preload();

    game.addScene(initMainScene);

	game.run();

    profiler::dumpBlocksToFile("../profiles/last_session_profile.prof");
    return 0;
}
