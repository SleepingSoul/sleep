#include "stdafx.h"
#include "DrawCall.h"
#include <Engine/Object.h>


BeginNamespaceSleep

DrawCall::DrawCall(Object* const object) noexcept(true)
    : m_texture(object->getTexture())
    , m_scale(object->getScale())
    , m_position(object->getPosition())
    , m_rotation(object->getRotation())
    , m_size(object->getSize())
    , m_topLeftUV(object->getTopLeftUV())
    , m_downRightUV(object->getDownRightUV())
    , m_color(object->getColor())
    , m_layer(object->getLayer())
{}

EndNamespaceSleep
