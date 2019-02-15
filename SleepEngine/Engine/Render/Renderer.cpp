#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
    : m_shader("Engine/Render/Shaders/shader.vs", "Engine/Render/Shaders/shader.fs")
{
    glEnable(GL_DEPTH_TEST);

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
    std::stable_sort(m_drawCalls.begin(), m_drawCalls.end());

    Texture* prevTexture = nullptr;

    for (auto const& drawCall : m_drawCalls)
    {
        auto& camera = GameWindow::instance().getCamera();
        /*auto const topLeft = camera.virtualPositionToNormalized({ position.x - size.x / 2, position.y + size.y / 2 }),
            topRight = camera.virtualPositionToNormalized({ position.x + size.x / 2, position.y + size.y / 2 }),
            downRight = camera.virtualPositionToNormalized({ position.x + size.x / 2, position.y - size.y / 2 }),
            downLeft = camera.virtualPositionToNormalized({ position.x - size.x / 2, position.y - size.y / 2 });*/
        glm::vec2 const normalizedPos = camera.virtualPositionToNormalized(drawCall.getPosition());

        glm::vec2 const topLeftUV = drawCall.getTopLeftUV();
        glm::vec2 const downRightUV = drawCall.getDownRightUV();
        glm::vec2 const topRightUV(downRightUV.x, topLeftUV.y);
        glm::vec2 const downLeftUV(topLeftUV.x, downRightUV.y);

        float const layer = static_cast <float>(drawCall.getLayer());

        float uv[] = {
            topRightUV.x, topRightUV.y,
            downRightUV.x, downRightUV.y,
            downLeftUV.x, downLeftUV.y,
            downLeftUV.x, downLeftUV.y,
            topLeftUV.x, topLeftUV.y,
            topRightUV.x, topRightUV.y
        };

        /*Clear buffers every frame*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_uvVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast <void*>(0));
        glEnableVertexAttribArray(1);

        auto* const currentTexture = drawCall.getTexture();
        if (currentTexture != prevTexture)
        {
            currentTexture->loadToGPU();
            prevTexture = currentTexture;
        }

        m_shader.use();

        // we use ONLY model and view matrices (since we don't need projection matrix for 2D graphix)
        glm::mat4 model(1.f);
        model = glm::scale(model, glm::vec3(drawCall.getScale(), 1.f));
        model = glm::rotate(model, glm::radians(drawCall.getRotation()), glm::vec3(0.f, 0.f, 1.f));

        glm::mat4 view(1.f);
        view = glm::translate(view, glm::vec3(normalizedPos, layer));

        m_shader.setMat4("model", model);
        m_shader.setMat4("view", view);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, currentTexture->getID());
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    m_drawCalls.clear();
}
