// Copyright 2019 Tihran Katolikian

#pragma once

#include <Engine/Render/Shader.h>


BeginNamespaceSleep

class Renderer
{
    ForbidCopyAndMove(Renderer)
public:
    using DrawCallsContainer = std::vector <DrawCall>;

    Renderer();

    void addDrawCall(DrawCall drawCall);
    template <class ...Args>
    void emplaceDrawCall(Args&&... args)
    {
        m_drawCalls.emplace_back(std::forward <Args>(args)...);
    }
    void render();

    void SetGPUMemoryBufferSize(size_t size) { m_gpuMemoryBufferSize = size; }
    size_t GetGPUMemoryBufferSize() const { return m_gpuMemoryBufferSize; }

private:
    Shader m_shader;
    DrawCallsContainer m_drawCalls;

    unsigned m_vertexVBO;
    unsigned m_uvVBO;
    unsigned m_VAO;

    size_t m_gpuMemoryBufferSize;
    size_t m_usedGPUMemory;
};

EndNamespaceSleep
