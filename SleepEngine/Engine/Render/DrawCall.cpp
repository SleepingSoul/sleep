#include "stdafx.h"


DrawCall::DrawCall(Texture* const texture, glm::vec2 const position, glm::vec2 const topLeftUV,
    glm::vec2 const downRightUV, Layer const layer)
    : m_texture(texture)
    , m_position(position)
    , m_topLeftUV(topLeftUV)
    , m_downRightUV(downRightUV)
    , m_layer(layer)
{}
