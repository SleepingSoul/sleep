#include "stdafx.h"
#include "Object.h"

Object::Object()
    : m_color(0xff, 0xff, 0xff, 0xff)
    , m_position(0.f, 0.f)
    , m_size(1.f, 1.f)
    , m_texture(nullptr)
    , m_layer(0)
{}

void Object::render()
{
    GameWindow::instance().getRenderer().addDrawCall({ m_texture, m_layer });
}
