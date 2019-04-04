// copyright 2019 Taras Martyniuk, Tihran Katolikian

#pragma once

#include <Engine/Systems/System.h>


BEGIN_NAMESPACE_SLEEP

class ResourceManager;
class System;

// stores and updates all game objects in a tree,
// stores all other engine objects as components
// only one instance exists, can be accessed globally
// use scene initer to define start state of your world
// usage: Game(sceneIniter).run(); // in your game's entry point
class Game
{
public:
    using Base = ObjectTree;
    using Scene = ObjectTree;
    using SceneIniter = std::function <void(Scene&)>;
    using SceneAndInitter = std::pair <Scene, SceneIniter>;
    using SceneIDType = unsigned;
    using ScenesContainer = std::unordered_map <SceneIDType, SceneAndInitter>;
    using SystemsContainer = std::vector <std::unique_ptr <System>>;

    static Game& instance() { return *m_instance; }

    Game(size_t width, size_t height);

    REF_GETTERS(getClock, m_clock)
    REF_GETTERS(getRenderer, *m_renderer)
    REF_GETTERS(getResourceManager, *m_resourceManager)
    REF_GETTERS(getCamera, m_camera)

    SceneIDType addScene(SceneIniter initer);

    Scene* findScene(SceneIDType id);
    Scene const* findScene(SceneIDType id) const;

    bool tryRemoveScene(SceneIDType id);

    void changeScene(SceneIDType id);

    void addSystem(SystemsContainer::value_type&& system);

    void run();

private:
    inline static NotOwnedPtr <Game> m_instance = nullptr;

    GameWindow m_window;
    Clock m_clock;
    Camera m_camera;

    std::unique_ptr <GameRenderer> m_renderer;
    std::unique_ptr <ResourceManager> m_resourceManager;

    SceneIDType m_nextSceneID;
    ScenesContainer m_scenes;
    ScenesContainer::iterator m_currentScene;

    SystemsContainer m_systems;

    void runFrame();
    void setupLogger();

    void initCurrentScene();
};

END_NAMESPACE_SLEEP
