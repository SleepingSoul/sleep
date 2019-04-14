// Copyright 2019, Tihran Katolikian
#include <Engine/Config/EngineConfig.h>
#pragma once

BEGIN_NAMESPACE_SLEEP

inline float metersToPixels(float meters)
{
    return meters * globalEngineConfig()->getData().MeterLengthInPixels / 2.f;
}

inline glm::vec2 metersToPixels(glm::vec2 sizeInMeters)
{
    return sizeInMeters * static_cast <float>(globalEngineConfig()->getData().MeterLengthInPixels) / 2.f;
}

inline float pixelsToMeters(float pixels)
{
    return pixels * 2.f / globalEngineConfig()->getData().MeterLengthInPixels;
}

inline glm::vec2 pixelsToMeters(glm::vec2 sizeInPixels)
{
    return sizeInPixels * 2.f / static_cast <float>(globalEngineConfig()->getData().MeterLengthInPixels);
}

END_NAMESPACE_SLEEP
