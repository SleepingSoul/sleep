#pragma once

class GameWindow
{
public:
    GameWindow(size_t width, size_t height, std::string_view title, Color bgColor = { 0xff, 0xff, 0xff, 0xff });
    ~GameWindow();

    Color getBackgroundColor() const { return m_bgColor; }
    void setBackgroundColor(Color const color) { m_bgColor = color; }
    bool isValid() const;
    operator bool() const;
    Renderer& getRenderer() { return m_renderer; }
    bool shouldClose() const;
    void runFrame();

    static GameWindow& instance();

private:
    Color m_bgColor;
    NotOwnedPtr <GLFWwindow> m_window;
    Renderer m_renderer;
    inline static NotOwnedPtr <GameWindow> m_instance = nullptr;
};
