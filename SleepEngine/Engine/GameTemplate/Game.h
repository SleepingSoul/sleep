// copyright 2019 Taras Martyniuk, Tihran Katolikian

#pragma once

#include <Engine/Systems/System.h>
#include <Engine/Config/ConfigManager.h>


BEGIN_NAMESPACE_SLEEP

class ResourceManager;
class ISystem;

// stores and updates all game objects in a tree,
// stores all other engine objects as components
// only one instance exists, can be accessed globally
// use scene initer to define start state of your world
// usage: Game(sceneIniter).run(); // in your game's entry point
class Game
{
public:
    using ScenesContainer = std::vector <Scene>;
    using SystemsContainer = std::vector <std::unique_ptr <ISystem>>;

    static Game& instance() { return *m_instance; }

    Game(size_t width, size_t height);

    REF_GETTERS(getClock, m_clock)
    REF_GETTERS(getRenderer, *m_renderer)
    REF_GETTERS(getResourceManager, *m_resourceManager)
    REF_GETTERS(getCamera, m_camera)
    REF_GETTERS(getConfigManager, m_configManager)
    REF_GETTERS(getEntityManager, m_entityManager)

    void addScene(Scene::Initer initer, std::string_view id);
    void changeActiveSceneTo(std::string_view id);

    void addSystem(SystemsContainer::value_type&& system);

    void run();

private:
    inline static NotOwnedPtr <Game> m_instance = nullptr;

    GameWindow m_window;
    Clock m_clock;
    Camera m_camera;
    ConfigManager m_configManager;

    std::unique_ptr <GameRenderer> m_renderer;
    std::unique_ptr <ResourceManager> m_resourceManager;

    ScenesContainer m_scenes;
    ScenesContainer::iterator m_currentScene;

    SystemsContainer m_systems;

    EntityManager m_entityManager;

    void runFrame();
    void setupLogger();
};

END_NAMESPACE_SLEEP

#include "global_shortcuts.h"
