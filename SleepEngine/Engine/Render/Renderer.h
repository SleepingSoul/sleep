#pragma once

class Renderer
{
public:
    using DrawCallsContainer = std::vector <DrawCall>;

    void addDrawCall(DrawCall drawCall);

private:
    DrawCallsContainer m_drawCalls;
};
