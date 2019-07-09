// copyright 2019 Taras Martyniuk

#include "stdafx.h"
#include <Engine/Camera.h>
#include <Engine/Clock.h>
#include <Engine/GameWindow.h>
#include <Engine/ResourceManagement/ResourceManager.h>
#include <Engine/Config/EngineConfig.h>
#include <Engine/Render/UpdateRenderBridge.h>
#include <Engine/Jobs/JobSystem.h>
#include <Engine/Systems/UpdateJob.h>


BEGIN_NAMESPACE_SLEEP

namespace
{
    // todo make config file
    float const FPS = 60.f;
}

Game::Game(size_t width, size_t height)
    : m_clock(FPS)
    , m_camera(width, height)
    , m_window(width, height, "Heroes of The Storm")
    , m_resourceManager(std::make_unique<ResourceManager>())
    , m_updateRenderBridge(std::make_unique<UpdateRenderBridge>())
{
    setupLogger();

    m_configManager.addConfig<EngineConfig>();
    m_configManager.loadAllConfigs();

    if (m_instance)
    {
	    LOG_AND_ASSERT_ERROR(false, "Attempt to create second game! It is forbidden!");
	    return;
    }
    m_renderer = std::make_unique <GameRenderer>();
    m_jobSystem = std::make_unique<JobSystem>();

    m_instance = this;
}

void Game::addScene(Scene::Initer initer, std::string_view id)
{
    auto& scene = m_scenes.emplace_back(std::move(initer), id);

    if (m_scenes.size() == 1)
    {
        m_sceneID = id;
    }
}

void Game::applyScene(std::string_view sceneID)
{
    auto const isSceneFound = [this, sceneID](auto const& scene)
    {
        return scene.getID() == sceneID;
    };

    auto const[found, it] = findIf(m_scenes, isSceneFound);

    if (!found)
    {
        LOG_AND_FAIL("Invalid current scene: {}", m_currentSceneID);
        return;
    }

    it->init();

    m_currentSceneID = sceneID;
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
    if (m_sceneID != m_currentSceneID)
    {
        EASY_BLOCK("Scene initialization", profiler::colors::Blue400);
        applyScene(m_sceneID);
        EASY_END_BLOCK;
    }

    if (!m_currentSceneID.empty())
    {
        if (m_isFirstFrame)
        {
            m_jobSystem->schedule(createUpdateJob());
            m_isFirstFrame = false;
        }

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

