#pragma once

class GameWindow
{
    ForbidCopyAndMove(GameWindow)
public:
    GameWindow(size_t width, size_t height, std::string_view title, Color bgColor = { 0xff, 0xff, 0xff, 0xff });
    ~GameWindow();

    Color getBackgroundColor() const { return m_bgColor; }
    void setBackgroundColor(Color const color) { m_bgColor = color; }

    bool isValid() const;
    operator bool() const;

    Renderer& getRenderer() { return *m_renderer; }

    ResourceManager& getResourceManager() { return m_resourceManager; }

    Camera& getCamera() { return m_camera; }

    bool shouldClose() const;

    void runFrame();

    static GameWindow& instance();

private:
    Color m_bgColor;
    NotOwnedPtr <GLFWwindow> m_window;
    std::unique_ptr <Renderer> m_renderer;
    ResourceManager m_resourceManager;
    Camera m_camera;
    inline static NotOwnedPtr <GameWindow> m_instance = nullptr;
};
