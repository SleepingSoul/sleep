#pragma once

BEGIN_NAMESPACE_SLEEP

constexpr float FloatPrecisionError = 0.0001f;

inline glm::vec2 directionFromRotation(float rotationDeg)
{
    float const rotation = glm::radians(rotationDeg);
    glm::vec2 const top {0.f, 1.f};

    float const x = top.x * std::cos(rotation) - top.y * std::sin(rotation);
    float const y = top.x * std::sin(rotation) + top.y * std::cos(rotation);

    return { x, y };
}

// time is clamped to the range [0, 1].
// if start > finish, goes backwards
inline float lerp(float from, float to, float time)
{
    if (time <= 0.f)
    {
        return from;
    }
    if (time >= 1.f)
    {
        return to;
    }
    return from + ((to - from) * time);
}

inline bool approximatelyEqual(float a, float b, float error = FloatPrecisionError)
{
    return std::abs(a - b) <= error;
}

inline bool approximatelyGreaterEqual(float a, float b, float error = FloatPrecisionError)
{
    return std::abs(a - b) - error <= 0.f;
}

inline bool approximatelyLessEqual(float a, float b, float error = FloatPrecisionError)
{
    return std::abs(b - a) - error <= 0.f;
}

END_NAMESPACE_SLEEP
