#include "stdafx.h"
#include "Renderer.h"


void Renderer::addDrawCall(DrawCall const drawCall)
{
    m_drawCalls.push_back(drawCall);
}
