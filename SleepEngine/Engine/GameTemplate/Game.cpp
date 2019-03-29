// copyright 2019 Taras Martyniuk
#include "stdafx.h"
#include "Game.h"
#include <Engine/Camera.h>
#include <Engine/Clock.h>
#include <Engine/GameWindow.h>

BeginNamespaceSleep

namespace
{
    // todo make config file
    float const FPS = 60.f;
}

Game::Game(SceneIniter sceneIniter, size_t width, size_t height)
    : m_clock(FPS)
    , m_camera(width, height)
    , m_window(width, height, "Heroes of the storm")
{
    setupLogger();

    if (m_instance)
    {
	    logAndAssertError(false, "Attempt to create second game window! It is forbidden!");
	    return;
    }
    m_instance = this;
    m_renderer = std::make_unique <GameRenderer>();

    if (!sceneIniter)
    {
	    logAndAssertError(false, "sceneIniter is null");
	    return;
    }
    sceneIniter(*this);
}

void Game::run()
{
    while (!m_window.shouldClose())
    {
	    runFrame();
    }
}

void Game::runFrame()
{
    EASY_FUNCTION(profiler::colors::Orange);
    m_clock.frameStart();

    Base::update(m_clock.getDT());

    m_renderer->render();

    m_window.runFrame();

    #ifdef SLEEP_ENABLE_CONSOLE_FRAMERATE_OUTPUT
    EASY_BLOCK("Console output", profiler::colors::Grey);
    std::cout << "FPS: " << m_clock.calculateFPS() << ", DT: " << m_clock.getDT() << '\n';
    EASY_END_BLOCK;
    #endif

    m_clock.frameEnd();
}

void Game::setupLogger()
{
    bool const rewriteOldLog = true;
    auto engineLogger = spdlog::basic_logger_mt(EngineLogger, EngineLoggerPath, rewriteOldLog);
    engineLogger->set_level(spdlog::level::debug);
}

EndNamespaceSleep

