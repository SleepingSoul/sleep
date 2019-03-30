#include "stdafx.h"
#include "Transform2DData.h"


BEGIN_NAMESPACE_SLEEP

Transform2DData::Transform2DData(glm::vec2 scale, glm::vec2 position, glm::vec2 size, Layer layer, float rotation) noexcept(true)
    : m_scale(scale)
    , m_position(position)
    , m_size(size)
    , m_layer(layer)
    , m_rotation(rotation)
{}

END_NAMESPACE_SLEEP
