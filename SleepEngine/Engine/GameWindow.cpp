#include "stdafx.h"
#include "GameWindow.h"


namespace
{
    unsigned const GLFWVersionMajor = 3;
    unsigned const GLFWVersionMinor = 3;
    void framebufferSizeCallback(GLFWwindow* const window, int const width, int const height)
    {
        glViewport(0, 0, width, height);
        GameWindow::instance().getCamera().setScreenSize(width, height);
    }
}

GameWindow::GameWindow(size_t const width, size_t const height, std::string_view const title, Color const bgColor)
    : m_bgColor(bgColor)
    , m_camera(width, height)
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
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    m_instance = this;

    if (!gladLoadGLLoader(reinterpret_cast <GLADloadproc>(glfwGetProcAddress)))
    {
        assertion(false, "Failed to initialize GLAD");
    }

    m_renderer = std::make_unique <Renderer>();
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
    glClearColor(m_bgColor.r, m_bgColor.g, m_bgColor.b, m_bgColor.a);
    glClear(GL_COLOR_BUFFER_BIT);

    m_renderer->render();

    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

GameWindow& GameWindow::instance()
{
    return *m_instance;
}
