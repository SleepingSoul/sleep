// copyright 2019 Taras Martyniuk, Tihran Katolikian
#pragma once
class GameWindow;
class Clock;
class Camera;

BEGIN_NAMESPACE_SLEEP

// stores and updates all game objects in a tree,
// stores all other engine objects as components
// only one instance exists, can be accessed globally
// use scene initer to define start state of your world
// usage: Game(sceneIniter).run(); // in your game's entry point
class Game: public ObjectTree
{
public:
    using Base = ObjectTree;
    using SceneIniter = std::function<void(Game&)>;

    static Game& instance() { return *m_instance; }

    Game(SceneIniter sceneIniter, size_t width, size_t height);

    REF_GETTERS(getClock, m_clock)
    REF_GETTERS(getRenderer, *m_renderer)
    REF_GETTERS(getResourceManager, m_resourceManager)
    REF_GETTERS(getCamera, m_camera)

    void run();


private:
    inline static NotOwnedPtr <Game> m_instance = nullptr;

    GameWindow m_window;
    Clock m_clock;
    Camera m_camera;
    std::unique_ptr <GameRenderer> m_renderer;
    ResourceManager m_resourceManager;

    void runFrame();
    void setupLogger();
};

END_NAMESPACE_SLEEP
