#include "stdafx.h"
#include "GameWindow.h"


BeginNamespaceSleep

namespace
{
    float const FPS = 60.f;

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
    , m_clock(FPS)
{
    SetupLogger();

    if (m_instance)
    {
        logAndAssertError(false, "Attempt to create second game window! It is forbidden!");
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
        logAndAssertError(false, "Window wasn't created!");
        return;
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    m_instance = this;

    if (!gladLoadGLLoader(reinterpret_cast <GLADloadproc>(glfwGetProcAddress)))
    {
        logAndAssertError(false, "Failed to initialize GLAD");
        return;
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
    EASY_FUNCTION(profiler::colors::Orange);
    m_clock.frameStart();

    update();
    render();

    m_renderer->render();

    EASY_BLOCK("Swap buffers/poll events", profiler::colors::Purple);
    glfwSwapBuffers(m_window);
    glfwPollEvents();
    EASY_END_BLOCK;

#ifdef SLEEP_ENABLE_CONSOLE_FRAMERATE_OUTPUT
    EASY_BLOCK("Console output", profiler::colors::Grey);
    std::cout << "FPS: " << m_clock.calculateFPS() << ", DT: " << m_clock.getDT() << '\n';
    EASY_END_BLOCK;
#endif

    m_clock.frameEnd();
}

GameWindow& GameWindow::instance()
{
    return *m_instance;
}

void GameWindow::SetupLogger() const
{
    bool const rewriteOldLog = true;
    auto engineLogger = spdlog::basic_logger_mt(EngineLogger, EngineLoggerPath, rewriteOldLog);
    engineLogger->set_level(spdlog::level::debug);
}

EndNamespaceSleep
