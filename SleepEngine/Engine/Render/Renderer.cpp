#include "stdafx.h"
#include "Renderer.h"
#include <Engine/EngineConfig.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>


namespace
{
    // Offset, that is set between all objects in one layer to make blending work
    float const OffsetBetweenLayers = 0.001f;

    // Near and Far distances for our ortho view matrix.
    // Far distance define the max number of Layers
    float const NearDistance = -1.f;
    float const FarDistance = slp::MaxLayer + 1;
}

BeginNamespaceSleep

Renderer::Renderer()
    : m_shader("Engine/Render/Shaders/shader.vs", "Engine/Render/Shaders/shader.fs")
    , m_gpuMemoryBufferSize(1000)
    , m_usedGPUMemory(0)
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
    EASY_FUNCTION(profiler::colors::Red);

    auto bgColor = GameWindow::instance().getBackgroundColor();
    glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    /*Clear buffers every frame*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    EASY_BLOCK("Sort draw calls");
    std::sort(m_drawCalls.begin(), m_drawCalls.end());
    EASY_END_BLOCK;

    float lastLayer = static_cast <float>(m_drawCalls.front().getLayer());
    float nextLayerOffset = 0.f;

    for (auto const& drawCall : m_drawCalls)
    {
        EASY_BLOCK("render draw call");
        if (drawCall.getLayer() != lastLayer)
        {
            lastLayer = static_cast <float>(drawCall.getLayer());
            nextLayerOffset = 0.f;
        }

        auto& camera = GameWindow::instance().getCamera();

        glm::vec2 const normalizedPos = camera.virtualPositionToNormalized(drawCall.getPosition());

        glm::vec2 const normalizedSize = camera.virtualSizeToNormalized(drawCall.getSize());

        glm::vec2 const topLeftUV = drawCall.getTopLeftUV();
        glm::vec2 const downRightUV = drawCall.getDownRightUV();
        glm::vec2 const topRightUV(downRightUV.x, topLeftUV.y);
        glm::vec2 const downLeftUV(topLeftUV.x, downRightUV.y);

        float const layer = MaxLayer - (static_cast <float>(drawCall.getLayer()) + nextLayerOffset);
        nextLayerOffset += OffsetBetweenLayers;

        float uv[] = {
            topRightUV.x, topRightUV.y,
            downRightUV.x, downRightUV.y,
            downLeftUV.x, downLeftUV.y,
            downLeftUV.x, downLeftUV.y,
            topLeftUV.x, topLeftUV.y,
            topRightUV.x, topRightUV.y
        };

        EASY_BLOCK("Load UV in GPU");
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_uvVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), reinterpret_cast <void*>(0));
        glEnableVertexAttribArray(1);
        EASY_END_BLOCK;

        // TODO: preload textures to GPU to avoid huge first frame dt?
        auto& currentTexture = *drawCall.getTexture();
        if (!currentTexture.isInGPU())
        {
            currentTexture.loadToGPU();
        }

        m_shader.use();

        EASY_BLOCK("MVP matrices load to GPU");
        glm::mat4 modelview(1.f);
        modelview = glm::translate(modelview, glm::vec3(normalizedPos, -layer));
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
             NearDistance,
             FarDistance
        );

        m_shader.setMat4("modelview", modelview);
        m_shader.setMat4("projection", projection);
        m_shader.setVec4("ColorMask", drawCall.getColor());
        EASY_END_BLOCK;

        EASY_BLOCK("OpenGL render");
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, currentTexture.getID());
        glDrawArrays(GL_TRIANGLES, 0, 6);
        EASY_END_BLOCK;
        EASY_END_BLOCK;
    }

    m_drawCalls.clear();
}

EndNamespaceSleep
