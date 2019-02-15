#include "stdafx.h"
#include "Object.h"

Object::Object() noexcept(true)
    : m_color(0xff, 0xff, 0xff, 0xff)
    , m_scale(1.f, 1.f)
    , m_position(0.f, 0.f)
    , m_size(1.f, 1.f)
    , m_topLeftUV(0.f, 0.f)
    , m_downRightUV(1.f, 1.f)
    , m_texture(nullptr)
    , m_layer(0)
    , m_rotation(0.f)
{}

void Object::setUV(float const topLeftX, float const topLeftY, float const downRightX, const float downRightY)
{
    m_topLeftUV = { topLeftX, topLeftY };
    m_downRightUV = { downRightX, downRightY };
}

void Object::render()
{
    GameWindow::instance().getRenderer().addDrawCall({ this });
}
