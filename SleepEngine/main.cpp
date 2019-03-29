#include <stdafx.h>

// settings
namespace
{
	size_t const WindowWidth = 1920;
	size_t const WindowHeight = 1080;
}

int main()
{
    EASY_PROFILER_ENABLE;

	// right now the heap allocated objects leak because Updator does not own them, fixed in Updator re-do by tihran
    auto initScene = [](slp::Game& game)
    {
        auto background = slp::createRenderableObject();

        auto* const renderer = background->getComponent <slp::Renderer>();
        auto* const transform2D = background->getComponent <slp::Transform2D>();

        renderer->setTexture(game.getResourceManager().getTexture("Data/orphea.jpg"));
        transform2D->getData().size = slp::pixelsToMeters(game.getCamera().getScreenSize());
        transform2D->getData().layer = 0;

        game.addToRoot(std::move(background));

        auto ciriTexture = game.getResourceManager().getTexture("Data/cirilla.png");

        for (int i = 0; i < 200; i++)
        {
            auto ciri = slp::createRenderableObject();

            auto* const renderer = ciri->getComponent <slp::Renderer>();
            auto* const transform2D = ciri->getComponent <slp::Transform2D>();

	        renderer->setTexture(ciriTexture);
	        transform2D->getData().layer = 1;
	        transform2D->getData().rotation = static_cast <float>(i) * 4.4f;
	        transform2D->getData().size = slp::pixelsToMeters(ciriTexture->getSize());
	        transform2D->getData().position = { -slp::pixelsToMeters(game.getCamera().getScreenWidth() / 2.f) + i++ / 20.f, 0.f };
	        game.addToRoot(std::move(ciri));
        }
    };

	slp::Game game(initScene, WindowWidth, WindowHeight);

    game.getClock().setFPS(60.f);
	game.getClock().setRestrictFPS(true);

	game.run();

    profiler::dumpBlocksToFile("../profiles/last_session_profile.prof");
    return 0;
}
