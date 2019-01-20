#include "stdafx.h"
#include "Object.h"

Object::Object()
    : m_color(0xff, 0xff, 0xff, 0xff)
    , m_position(0.f, 0.f)
    , m_size(1.f, 1.f)
    , m_texture(nullptr)
    , m_layer(0)
{}

void Object::setUV(float const topLeftX, float const topLeftY, float const downRightX, const float downRightY)
{
    m_topLeftUV = { topLeftX, topLeftY };
    m_downRightUV = { downRightX, downRightY };
}

void Object::render()
{
    DrawCall const drawCall(m_texture, m_position, m_size, m_topLeftUV, m_downRightUV, m_layer);
    GameWindow::instance().getRenderer().addDrawCall(drawCall);
}
