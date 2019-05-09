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
    , m_window(width, height, "Heroes of the storm")
    , m_nextSceneID(0)
    , m_resourceManager(std::make_unique<ResourceManager>())
    , m_updateRenderBridge(std::make_unique<UpdateRenderBridge>())
{
    m_currentScene = m_scenes.end();

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

Game::SceneIDType Game::addScene(SceneIniter initer)
{
    auto sceneAndIniter = std::make_pair(Scene(), initer);
    auto [it, wasInserted] = m_scenes.insert({ m_nextSceneID++, std::move(sceneAndIniter) });
    assertion(wasInserted, "nextSceneID overflow");

    if (m_scenes.size() == 1)
    {
        m_currentScene = it;
        initCurrentScene();
    }

    return it->first;
}

Game::Scene* Game::findScene(SceneIDType id)
{
    auto it = m_scenes.find(id);

    return it != m_scenes.end() ? &it->second.first : nullptr;
}

Game::Scene const* Game::findScene(SceneIDType id) const
{
    return const_cast <Game*>(this)->findScene(id);
}

bool Game::tryRemoveScene(SceneIDType id)
{
    auto it = m_scenes.find(id);

    if (it == m_scenes.end())
    {
        return false;
    }

    m_scenes.erase(it);
    return true;
}

void Game::changeScene(SceneIDType id)
{
    auto it = m_scenes.find(id);

    if (it == m_currentScene)
    {
        return;
    }

    m_currentScene->second.first.clear();
    m_currentScene = it;

    initCurrentScene();
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
    //EASY_FUNCTION(profiler::colors::Orange);

    if (m_currentScene != m_scenes.end())
    {
        if (m_isFirstFrame)
        {
            auto& objectTree = m_currentScene->second.first;
            m_jobSystem->schedule(std::make_unique<UpdateJob>(objectTree));
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

    //m_clock.frameEnd();
}

void Game::setupLogger()
{
    bool const rewriteOldLog = true;
    auto engineLogger = spdlog::basic_logger_mt(EngineLogger, EngineLoggerPath, rewriteOldLog);
    engineLogger->set_level(spdlog::level::debug);
}

void Game::initCurrentScene()
{
    auto& [scene, initer] = m_currentScene->second;
    initer(scene);
}

END_NAMESPACE_SLEEP

