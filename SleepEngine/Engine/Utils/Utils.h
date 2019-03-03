// Copyright 2019, Tihran Katolikian

#pragma once

BeginNamespaceSleep

template <class T>
using NotOwnedPtr = T*;

inline float metersToPixels(float const meters)
{
    return meters * MeterLengthInPixels / 2.f;
}

inline float pixelsToMeters(float const pixels)
{
    return pixels * 2.f / MeterLengthInPixels;
}

inline glm::vec2 sizeInMetersToPixels(glm::vec2 const sizeInMeters)
{
    return sizeInMeters * static_cast <float>(MeterLengthInPixels) / 2.f;
}

inline glm::vec2 sizeInPixelsToMeters(glm::vec2 const sizeInPixels)
{
    return sizeInPixels * 2.f / static_cast <float>(MeterLengthInPixels);
}

inline glm::vec2 positionInMetersToPixels(glm::vec2 const positionInMeters)
{
    return sizeInMetersToPixels(positionInMeters);
}

inline glm::vec2 positionInPixelsToMeters(glm::vec2 const positionInPixels)
{
    return sizeInPixelsToMeters(positionInPixels);
}

inline glm::vec2 calculateLesserInsertionSize(glm::vec2 const foregroundItemSize, glm::vec2 const backgroundItemSize)
{
    auto const bgRatio = backgroundItemSize.x / backgroundItemSize.y;

    float x = foregroundItemSize.x;
    float y = foregroundItemSize.y;

    if (bgRatio > 1.f)
    {
        y += backgroundItemSize.y - foregroundItemSize.y;
        x = std::min(foregroundItemSize.x * y / foregroundItemSize.y, x + backgroundItemSize.x - foregroundItemSize.x);
    }
    else
    {
        x += backgroundItemSize.x - foregroundItemSize.x;
        y = std::min(foregroundItemSize.y * x / foregroundItemSize.x, y + backgroundItemSize.y - foregroundItemSize.y);
    }

    return { x, y };
}

EndNamespaceSleep
