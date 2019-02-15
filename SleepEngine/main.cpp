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

    Object object;
    object.setSize({ 1, 1 });
    //object.setScale({ 0.5f, 0.5f });
    //object.setDownRightUV({ 1.f, 0.6f });
    object.setRotation(0.f);
    object.setLayer(8);
    object.setPosition({ 0, 0 });
    object.setTexture(window.getResourceManager().getTexture("Data/CJ9qfDJ.jpg"));

    Object o2;
    o2.setPosition({ 1, 0 });
    o2.setSize({ 1, 1 });
    o2.setTexture(window.getResourceManager().getTexture("Data/CJ9qfDJ.jpg"));
    o2.setRotation(0.f);
    o2.setLayer(4);

    Object o3;
    o3.setTexture(window.getResourceManager().getTexture("Data/CJ9qfDJ.jpg"));
    o3.setPosition({ 1, 1 });
    o3.setSize({ 1, 1 });

    while (!window.shouldClose())
    {
        o3.render();
        o2.render();
        object.render();
        window.runFrame();
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