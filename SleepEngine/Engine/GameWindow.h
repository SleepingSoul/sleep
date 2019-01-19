#pragma once

class GameWindow
{
public:
    GameWindow(size_t width, size_t height, std::string_view title);
    ~GameWindow();

    bool isValid() const;
    operator bool() const;
    Renderer& getRenderer() { return m_renderer; }

    static GameWindow& instance();

private:
    NotOwnedPtr <GLFWwindow> m_window;
    Renderer m_renderer;
    inline static NotOwnedPtr <GameWindow> m_instance = nullptr;
};
