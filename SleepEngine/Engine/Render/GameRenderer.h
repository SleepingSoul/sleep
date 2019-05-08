// Copyright 2019 Tihran Katolikian

#pragma once

#include <Engine/Render/Shader.h>


BEGIN_NAMESPACE_SLEEP

class GameRenderer
{
    FORBID_COPY_AND_MOVE(GameRenderer)
public:
    //using DrawCallsContainer = std::vector <DrawCall>;

    GameRenderer();

    void render();

    REF_GET_SET(Color, getBackgroundColor, setBackgroundColor, m_backgroundColor)

private:
    Shader m_shader;
    //DrawCallsContainer m_drawCalls;

    unsigned m_vertexVBO;
    unsigned m_uvVBO;
    unsigned m_VAO;

    Color m_backgroundColor;
};

END_NAMESPACE_SLEEP
