#include "stdafx.h"
#include "GameWindow.h"
#include <Engine/EngineConfig.h>
#include <Engine/GameTemplate/Game.h>

BEGIN_NAMESPACE_SLEEP

namespace
{
    unsigned const GLFWVersionMajor = 3;
    unsigned const GLFWVersionMinor = 3;

    void framebufferSizeCallback(GLFWwindow* const window, int const width, int const height)
    {
        glViewport(0, 0, width, height);
        Game::instance().getCamera().setScreenSize(width, height);
    }
}

GameWindow::GameWindow(size_t width, size_t height, std::string_view title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFWVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFWVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    m_window = glfwCreateWindow(width, height, title.data(), NULL, NULL);
    if (!m_window)
    {
        logAndAssertError(false, "Window wasn't created!");
        return;
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

    if (!gladLoadGLLoader(reinterpret_cast <GLADloadproc>(glfwGetProcAddress)))
    {
        logAndAssertError(false, "Failed to initialize GLAD");
        return;
    }
}

GameWindow::~GameWindow()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool GameWindow::isValid() const
{
    return m_window;
}

GameWindow::operator bool() const
{
    return isValid();
}

bool GameWindow::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void GameWindow::runFrame()
{
    EASY_FUNCTION(profiler::colors::Orange);
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

END_NAMESPACE_SLEEP
