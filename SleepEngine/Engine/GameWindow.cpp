#include "stdafx.h"
#include "GameWindow.h"


namespace
{
    unsigned const GLFWVersionMajor = 3;
    unsigned const GLFWVersionMinor = 3;
}

GameWindow::GameWindow(size_t const width, size_t const height, std::string_view const title)
{
    if (m_instance)
    {
        return;
    }

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
        assertion(false, "Window wasn't created!");
    }
    glfwMakeContextCurrent(m_window);
    m_instance = this;
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

GameWindow& GameWindow::instance()
{
    assertion(!m_instance, "Attempt to create few windows in one program!");
    return *m_instance;
}
