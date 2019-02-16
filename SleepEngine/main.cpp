#include "stdafx.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 300;
const unsigned int SCR_HEIGHT = 300;

using namespace slp;

int main()
{
    GameWindow window(SCR_WIDTH, SCR_HEIGHT, "I dont like sand", { 0.2f, 1.f, 0.2f, 1.f });
    assert(window.isValid());
    window.getClock().setRestrictFPS(true);

    Object object;
    object.setSize({ 4, 4 });
    object.setDownRightUV({ 1.f, 0.5f });
    object.setLayer(8);
    object.setPosition({ 0, 0 });
    object.setTexture(window.getResourceManager().getTexture("Data/CJ9qfDJ.jpg"));

    Object o2;
    o2.setPosition({ 4, 0 });
    o2.setSize({ 4, 4 });
    o2.setTexture(window.getResourceManager().getTexture("Data/CJ9qfDJ.jpg"));
    o2.setRotation(45.f);
    o2.setLayer(4);
    o2.modifyColor().a = 0.5f;

    Object o3;
    o3.setTexture(window.getResourceManager().getTexture("Data/red.png"));
    o3.setPosition({ 4, 4 });
    o3.setSize({ 4, 4 });
    o3.setScale({ 0.5f, 1.f });
    o3.setColor({ 0.5f, 0.5f, 0.5f, 0.4f });

    while (!window.shouldClose())
    {
        window.getClock().frameStart();

        o3.render();
        o2.render();
        object.render();
        window.runFrame();

        window.getClock().frameEnd();
        std::cout << "FPS: " << window.getClock().calculateFPS() << ", DT: " << window.getClock().getDT() << '\n';
    }

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    //GameWindow::instance().getCamera().setScreenSize(width, height);
    glViewport(0, 0, width, height);
}