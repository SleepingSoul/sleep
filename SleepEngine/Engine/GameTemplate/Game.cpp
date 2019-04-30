// copyright 2019 Taras Martyniuk

#include "stdafx.h"
#include <Engine/Camera.h>
#include <Engine/Clock.h>
#include <Engine/GameWindow.h>
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Engine/Config/EngineConfig.h>


BEGIN_NAMESPACE_SLEEP

namespace
{
    // todo make config file
    float const FPS = 60.f;
}

Game::Game(size_t width, size_t height)
    : m_clock(FPS)
    , m_camera(width, height)
    , m_window(width, height, "Heroes of the storm")
    , m_resourceManager(std::make_unique <ResourceManager>())
{
    m_currentScene = m_scenes.end();

    setupLogger();

    m_configManager.addConfig<EngineConfig>();
    m_configManager.loadAllConfigs();

    if (m_instance)
    {
        LOG_AND_ASSERT_ERROR(false, "Attempt to create second game window! It is forbidden!");
        return;
    }
    m_instance = this;
    m_renderer = std::make_unique <GameRenderer>();
}

void Game::addScene(Scene::Initer initer, std::string_view id)
{
    auto& scene = m_scenes.emplace_back(std::move(initer), id);

    if (m_scenes.size() == 1)
    {
        // first scene
        scene.init();
        m_currentScene = m_scenes.begin();
    }
}

void Game::changeActiveSceneTo(std::string_view id)
{
    auto const isSceneFound = [id](auto const& scene)
    {
        return scene.getID() == id;
    };

    auto const[found, it] = findIf(m_scenes, isSceneFound);

    if (!found)
    {
        LOG_AND_FAIL("No scene found with id: {}", id);
        return;
    }

    spdlog::get(EngineLogger)->info("Changing scene '{}' to '{}'.", m_currentScene->getID(), id);

    m_entityManager.clear();
    
    it->init();
}

void Game::addSystem(SystemsContainer::value_type&& system)
{
    m_systems.emplace_back(std::move(system));
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

    if (m_currentScene != m_scenes.end())
    {
        auto const dt = m_clock.getDT();

        EASY_BLOCK("Update systems");
        for (auto& system : m_systems)
        {
            system->update(dt);
        }
        EASY_END_BLOCK;

        EASY_BLOCK("Entities update", profiler::colors::Amber100);
        m_entityManager.update(dt);
        EASY_END_BLOCK;

        m_renderer->render();
    }

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

END_NAMESPACE_SLEEP

