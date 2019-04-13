#include "stdafx.h"
#include <Engine/Components/Transform2D.h>
#include "DrawCall.h"
#include <Engine/Object.h>


BEGIN_NAMESPACE_SLEEP

DrawCall::DrawCall(Transform2DData const& transform, Texture* texture, glm::vec2 topLeftUV, glm::vec2 downRightUV, Color color)
    noexcept(std::is_nothrow_constructible_v <Transform2DData>)
    : m_transform(transform)
    , m_texture(texture)
    , m_topLeftUV(topLeftUV)
    , m_downRightUV(downRightUV)
    , m_color(color)
{}

END_NAMESPACE_SLEEP
