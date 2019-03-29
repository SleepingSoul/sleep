// Copyright 2019, Tihran Katolikian
#include <Engine/EngineConfig.h>
#pragma once

BeginNamespaceSleep

template <class T>
using NotOwnedPtr = T*;

inline float metersToPixels(float meters)
{
    return meters * MeterLengthInPixels / 2.f;
}

inline glm::vec2 metersToPixels(glm::vec2 sizeInMeters)
{
    return sizeInMeters * static_cast <float>(MeterLengthInPixels) / 2.f;
}

inline float pixelsToMeters(float pixels)
{
    return pixels * 2.f / MeterLengthInPixels;
}

inline glm::vec2 pixelsToMeters(glm::vec2 sizeInPixels)
{
    return sizeInPixels * 2.f / static_cast <float>(MeterLengthInPixels);
}

EndNamespaceSleep
