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

	slp::Game game([](slp::Game&) {}, WindowWidth, WindowHeight);

    game.getClock().setFPS(60.f);
	game.getClock().setRestrictFPS(true);

    slp::Object background;
    background.setTexture(game.getResourceManager().getTexture("Data/orphea.jpg"));
    background.setSize(slp::pixelsToMeters(game.getCamera().getScreenSize()));
    background.setLayer(0);
	game.addToRoot(&background);

    slp::Object cirillas[200];
    auto ciriTexture = game.getResourceManager().getTexture("Data/cirilla.png");

    {
        size_t i = 0;
        for (auto& c : cirillas)
        {
            c.setTexture(ciriTexture);
            c.setLayer(1);
            c.setRotation(static_cast <float>(i) * 4.4f);
            c.setSize(slp::pixelsToMeters(ciriTexture->getSize()));
            c.setPosition({ -slp::pixelsToMeters(game.getCamera().getScreenWidth() / 2.f) + i++ / 20.f, 0.f });
            game.addToRoot(&c);
        }
    }

	game.run();

    profiler::dumpBlocksToFile("../profiles/last_session_profile.prof");
    return 0;
}
