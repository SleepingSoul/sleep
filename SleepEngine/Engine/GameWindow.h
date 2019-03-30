// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class GameWindow
{
    FORBID_COPY_AND_MOVE(GameWindow)
public:
    GameWindow(size_t width, size_t height, std::string_view title);
    ~GameWindow();

    bool isValid() const;
    operator bool() const;

    bool shouldClose() const;

    void runFrame();

private:
    NotOwnedPtr <GLFWwindow> m_window;
};

END_NAMESPACE_SLEEP
