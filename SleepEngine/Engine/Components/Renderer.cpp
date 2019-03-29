#include "stdafx.h"
#include "Renderer.h"
#include <Engine/Components/Transform2D.h>


BeginNamespaceSleep

Renderer::Renderer() noexcept(true)
    : Base(getTypeID <Renderer>())
    , m_color(1.f, 1.f, 1.f, 1.f)
    , m_topLeftUV(0.f, 0.f)
    , m_downRightUV(1.f, 1.f)
    , m_texture(nullptr)
{}

void Renderer::update(float dt)
{
    auto* const transform = m_parent->getComponent <Transform2D>();
    
    if (!transform)
    {
        assertion(false, "Renderer component requires Transform2D component to be in parent object.");
        return;
    }

    Game::instance().getRenderer().emplaceDrawCall()
}

EndNamespaceSleep
