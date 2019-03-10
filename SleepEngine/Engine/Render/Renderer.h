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

    void setGPUMemoryBufferSize(size_t size) { m_gpuMemoryBufferSize = size; }
    size_t getGPUMemoryBufferSize() const { return m_gpuMemoryBufferSize; }

private:
    void renderLayer(DrawCallsContainer::iterator begin, DrawCallsContainer::iterator end);
    void renderOneTexturedDrawCalls(DrawCallsContainer::const_iterator begin, DrawCallsContainer::const_iterator end);

    Shader m_shader;
    DrawCallsContainer m_drawCalls;

    unsigned m_vertexVBO;
    unsigned m_uvVBO;
    unsigned m_VAO;

    // index of vertex (we always draw 2 triangles)
    unsigned m_elementBuffer;

    // color mask for each vertex
    unsigned m_colorMaskBuffer;

    // transform data for each vertex (translate position, rotation, scale)
    unsigned m_transformBuffer;

    size_t m_gpuMemoryBufferSize;
    size_t m_usedGPUMemory;
};

EndNamespaceSleep
