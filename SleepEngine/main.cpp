#include "stdafx.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1200;

int main()
{
    GameWindow window(SCR_WIDTH, SCR_HEIGHT, "I dont like sand", { 0.2f, 1.f, 0.2f, 1.f });
    assert((bool)window);

    Object object;
    object.setSize({ 500, 500 });
    //object.setScale({ 0.5f, 0.5f });
    //object.setDownRightUV({ 1.f, 0.6f });
    object.setRotation(-45.f);
    object.setLayer(0);
    object.setPosition({ 900.f, 0.f });
    object.setTexture(window.getResourceManager().getTexture("Data/detroit_become_human_wallpaper_by_cemreksdmr-dcd31yr.jpg"));

    /*Object o2;
    o2.setSize({ 800, 600 });
    o2.setTexture(window.getResourceManager().getTexture("Data/CJ9qfDJ.jpg"));
    o2.setLayer(9);*/

    while (!window.shouldClose())
    {
        //o2.render();
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
    glViewport(0, 0, width, height);
}