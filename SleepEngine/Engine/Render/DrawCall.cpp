#include "stdafx.h"
#include "DrawCall.h"
#include <Engine/Object.h>


BeginNamespaceSleep

DrawCall::DrawCall(Transform2D const& transform, Texture* texture, glm::vec2 topLeftUV, glm::vec2 downRightUV, Color color)
    noexcept(std::is_nothrow_constructible_v <Transform2D>)
    : m_transform(transform)
    , m_texture(texture)
    , m_topLeftUV(topLeftUV)
    , m_downRightUV(downRightUV)
    , m_color(color)
{}

EndNamespaceSleep
