#pragma once

BEGIN_NAMESPACE_SLEEP

inline float degToRad(float a) 
{
    return (a * M_PI) / 180.0f;
}

inline glm::vec2 directionFromRotation(float rotationDeg)
{
    float const rotation = degToRad(rotationDeg);
    glm::vec2 const top {0.f, 1.f};

    float const x = top.x * std::cos(rotation) - top.y * std::sin(rotation);
    float const y = top.x * std::sin(rotation) + top.y * std::cos(rotation);

    return { x, y };
}

END_NAMESPACE_SLEEP
