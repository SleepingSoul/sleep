// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

struct Transform2DData
{
    glm::vec2 Scale = {1.f, 1.f};
    glm::vec2 Position;
    glm::vec2 Size = {1.f, 1.f};
    LayerT Layer = 1;
    float Rotation = 0.f;
};

END_NAMESPACE_SLEEP
