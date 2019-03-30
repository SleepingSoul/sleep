// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

struct Transform2DData
{
    glm::vec2 scale;
    glm::vec2 position;
    glm::vec2 size;
    Layer layer;
    float rotation;
};

END_NAMESPACE_SLEEP
