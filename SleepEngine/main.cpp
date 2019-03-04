#include "stdafx.h"

// settings
namespace
{
    size_t const WindowWidth = 1920;
    size_t const WindowHeight = 1080;
    slp::Color WindowBgColor(0.003f, 0.007f, 0.298f, 1.f);
}

int main()
{
    EASY_PROFILER_ENABLE;
    profiler::startListen(9999);

    slp::GameWindow window(WindowWidth, WindowHeight, "Heroes of the storm", WindowBgColor);
    assert(window.isValid());
    window.getClock().setFPS(60.f);
    window.getClock().setRestrictFPS(true);

    slp::Object background;
    background.setTexture(window.getResourceManager().getTexture("Data/orphea.jpg"));
    background.setSize(slp::sizeInPixelsToMeters(window.getCamera().getScreenSize()));
    background.setLayer(0);
    window.addChild(&background);

    slp::Object cirillas[5000];
    auto ciriTexture = window.getResourceManager().getTexture("Data/cirilla.png");

    {
        size_t i = 0;
        for (auto& c : cirillas)
        {
            c.setTexture(ciriTexture);
            c.setLayer(1);
            c.setRotation(static_cast <float>(i) * 4.4f);
            c.setSize(slp::sizeInPixelsToMeters(ciriTexture->getSize()));
            c.setPosition({ -slp::pixelsToMeters(window.getCamera().getScreenWidth() / 2.f) + i++ / 40.f, 0.f });
            window.addChild(&c);
        }
    }

    while (!window.shouldClose())
    {
        window.runFrame();
        EASY_BLOCK("Output");
        std::cout << "FPS: " << window.getClock().calculateFPS() << ", DT: " << window.getClock().getDT() << '\n';
        EASY_END_BLOCK;
    }

    profiler::stopListen();
    return 0;
}
