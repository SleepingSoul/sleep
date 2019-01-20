#pragma once

class Renderer
{
public:
    using DrawCallsContainer = std::vector <DrawCall>;

    Renderer();

    void addDrawCall(DrawCall drawCall);
    void render();

private:
    DrawCallsContainer m_drawCalls;
    unsigned m_VBO;
    unsigned m_VAO;
    unsigned m_EBO;
};
