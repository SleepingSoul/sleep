// Copyright 2019 Tihran Katolikian

#pragma once

#include <glm/glm.hpp>
#include <Engine/Utils/MacroUtils.h>

BEGIN_NAMESPACE_SLEEP

struct RelativeTransform
{
    glm::vec2 Position{ 0.f, 0.f };
    float Rotation{ 0.f };
};

END_NAMESPACE_SLEEP
