#include "stdafx.h"
#include "Renderer.h"
#include <Engine/Components/Transform2D.h>


BEGIN_NAMESPACE_SLEEP

Renderer::Renderer() noexcept(true)
    : Base(getComponentTypeID <Renderer>())
    , m_color(1.f, 1.f, 1.f, 1.f)
    , m_topLeftUV(0.f, 0.f)
    , m_downRightUV(1.f, 1.f)
    , m_texture(nullptr)
{}

void Renderer::update(float dt)
{
    auto* const transform = m_object->getComponent <Transform2D>();
    
    if (!transform)
    {
        assertion(false, "Renderer component requires Transform2D component to be in parent object.");
        return;
    }

    Game::instance().getRenderer().emplaceDrawCall(transform->getData(), m_texture, m_topLeftUV, m_downRightUV, m_color);
}

END_NAMESPACE_SLEEP
