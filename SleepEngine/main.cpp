#include "stdafx.h"

// settings
namespace
{
    size_t const WindowWidth = 900;
    size_t const WindowHeight = 600;
    slp::Color WindowBgColor(0.003f, 0.007f, 0.298f, 1.f);
}

int main()
{
    slp::GameWindow window(WindowWidth, WindowHeight, "Heroes of the storm", WindowBgColor);
    assert(window.isValid());
    window.getClock().setRestrictFPS(true);

    slp::Object background;
    background.setTexture(window.getResourceManager().getTexture("Data/orphea.jpg"));
    background.setSize(slp::sizeInPixelsToMeters(window.getCamera().getScreenSize()));
    window.addChild(&background);

    while (!window.shouldClose())
    {
        window.runFrame();
        std::cout << "FPS: " << window.getClock().calculateFPS() << ", DT: " << window.getClock().getDT() << '\n';
    }

    return 0;
}
