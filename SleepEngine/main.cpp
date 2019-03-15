#include <stdafx.h>
#include <Engine/GameTemplate/Game.h>

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
        auto* background = new slp::Object();
        background->setTexture(game.getResourceManager().getTexture("Data/orphea.jpg"));
        background->setSize(slp::pixelsToMeters(game.getCamera().getScreenSize()));
        background->setLayer(0);
        game.addToRoot(background);

        auto ciriTexture = game.getResourceManager().getTexture("Data/cirilla.png");

        for (int i = 0; i < 200; i++)
        {
	        auto* ciri = new slp::Object();

	        ciri->setTexture(ciriTexture);
	        ciri->setLayer(1);
	        ciri->setRotation(static_cast <float>(i) * 4.4f);
	        ciri->setSize(slp::pixelsToMeters(ciriTexture->getSize()));
	        ciri->setPosition({ -slp::pixelsToMeters(game.getCamera().getScreenWidth() / 2.f) + i++ / 20.f, 0.f });
	        game.addToRoot(ciri);
        }
    };

	slp::Game game(initScene, WindowWidth, WindowHeight);

    game.getClock().setFPS(60.f);
	game.getClock().setRestrictFPS(true);

	game.run();

    profiler::dumpBlocksToFile("../profiles/last_session_profile.prof");
    return 0;
}
