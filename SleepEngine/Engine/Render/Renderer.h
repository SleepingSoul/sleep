#pragma once

#include <Engine/Render/Shader.h>

class Renderer
{
    ForbidCopyAndMove(Renderer)
public:
    using DrawCallsContainer = std::vector <DrawCall>;

    Renderer();

    void addDrawCall(DrawCall drawCall);
    void render();

private:
    Shader m_shader;
    DrawCallsContainer m_drawCalls;
    unsigned m_vertexVBO;
    unsigned m_uvVBO;
    unsigned m_VAO;
};
