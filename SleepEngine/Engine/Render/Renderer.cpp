#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    unsigned indices[] = { 0, 1, 3, 1, 2, 3 };
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Renderer::addDrawCall(DrawCall const drawCall)
{
    m_drawCalls.push_back(drawCall);
}

void Renderer::render()
{
    std::stable_sort(m_drawCalls.begin(), m_drawCalls.end());

    for (auto const& drawCall : m_drawCalls)
    {
        auto const position = drawCall.getPosition();
        auto const size = drawCall.getSize();
        auto& camera = GameWindow::instance().getCamera();
        auto const topLeft = camera.virtualPositionToNormalized({ position.x - size.x / 2, position.y + size.y / 2 }),
            topRight = camera.virtualPositionToNormalized({ position.x + size.x / 2, position.y + size.y / 2 }),
            downRight = camera.virtualPositionToNormalized({ position.x + size.x / 2, position.y - size.y / 2 }),
            downLeft = camera.virtualPositionToNormalized({ position.x - size.x / 2, position.y - size.y / 2 });
        float const layer = static_cast <float>(drawCall.getLayer());
        auto const topLeftUV = drawCall.getTopLeftUV();
        auto const downRightUV = drawCall.getDownRightUV();
        glm::vec2 const topRightUV(downRightUV.x, topLeftUV.y);
        glm::vec2 const downLeftUV(topLeftUV.x, downRightUV.y);

        float vertices[] = {
            topRight.x, topRight.y, layer, topRightUV.x, topRightUV.y,
            downRight.x, downRight.y, layer, downRightUV.x, downRightUV.y,
            downLeft.x, downLeft.y, layer, downLeftUV.x, downLeftUV.y,
            topLeft.x, topLeft.y, layer, topLeftUV.x, topLeftUV.y
        };

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast <void*>(0));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast <void*>(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, drawCall.getTexture()->getID());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
}
