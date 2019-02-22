#include "stdafx.h"
#include "Renderer.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>


BeginNamespaceSleep

Renderer::Renderer()
    : m_shader("Engine/Render/Shaders/shader.vs", "Engine/Render/Shaders/shader.fs")
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_vertexVBO);
    glGenBuffers(1, &m_uvVBO);

    glBindVertexArray(m_VAO);
    float vertices[] = {
             1,  1,
             1, -1,
            -1, -1,
            -1, -1,
            -1,  1,
             1,  1
    };

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast <void*>(0));
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

void Renderer::addDrawCall(DrawCall const drawCall)
{
    m_drawCalls.push_back(drawCall);
}

void Renderer::render()
{
    /*Clear buffers every frame*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::stable_sort(m_drawCalls.begin(), m_drawCalls.end());

    static Texture* prevTexture = nullptr;

    for (auto const& drawCall : m_drawCalls)
    {
        auto& camera = GameWindow::instance().getCamera();

        glm::vec2 const normalizedPos = camera.virtualPositionToNormalized(drawCall.getPosition());

        glm::vec2 const normalizedSize = camera.virtualSizeToNormalized(drawCall.getSize());

        glm::vec2 const topLeftUV = drawCall.getTopLeftUV();
        glm::vec2 const downRightUV = drawCall.getDownRightUV();
        glm::vec2 const topRightUV(downRightUV.x, topLeftUV.y);
        glm::vec2 const downLeftUV(topLeftUV.x, downRightUV.y);

        float const layer = -static_cast <float>(drawCall.getLayer());

        float uv[] = {
            topRightUV.x, topRightUV.y,
            downRightUV.x, downRightUV.y,
            downLeftUV.x, downLeftUV.y,
            downLeftUV.x, downLeftUV.y,
            topLeftUV.x, topLeftUV.y,
            topRightUV.x, topRightUV.y
        };

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_uvVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast <void*>(0));
        glEnableVertexAttribArray(1);

        auto* const currentTexture = drawCall.getTexture();
        if (currentTexture != prevTexture)
        {
            currentTexture->loadToGPU();
            prevTexture = currentTexture;
        }

        m_shader.use();

        glm::mat4 modelview(1.f);
        modelview = glm::translate(modelview, glm::vec3(normalizedPos, layer));
        modelview = glm::rotate(modelview, glm::radians(drawCall.getRotation()), glm::vec3(0.f, 0.f, 1.f));
        auto resultingScale = glm::vec3(drawCall.getScale() * normalizedSize, 1.f);
        modelview = glm::scale(modelview, resultingScale);

        float const scaleX = camera.getScreenWidth() / PrimaryWindowSize.x;
        float const scaleY = camera.getScreenHeight() / PrimaryWindowSize.y;

        glm::mat4 projection = glm::ortho(
            -scaleX,
             scaleX,
            -scaleY,
             scaleY,
             -1.f,
             100.f
        );

        m_shader.setMat4("modelview", modelview);
        m_shader.setMat4("projection", projection);
        m_shader.setVec4("ColorMask", drawCall.getColor());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, currentTexture->getID());
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    m_drawCalls.clear();
}

EndNamespaceSleep
