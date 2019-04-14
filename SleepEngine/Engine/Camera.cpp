#include "stdafx.h"
#include "Camera.h"


BEGIN_NAMESPACE_SLEEP

Camera::Camera(size_t const screenWidth, size_t const screenHeight)
    : m_screenWidth(screenWidth)
    , m_screenHeight(screenHeight)
{}

void Camera::setScreenSize(size_t const screenWidth, size_t const screenHeight)
{
    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;
}

glm::vec2 Camera::virtualPositionToNormalized(glm::vec2 const position) const
{
    EngineConfigData const& config = globalEngineConfig()->getData();
    return position / config.PrimaryWindowSize * static_cast <float>(config.MeterLengthInPixels);;
}

glm::vec2 Camera::virtualSizeToNormalized(glm::vec2 const size) const
{
    return virtualPositionToNormalized(size) / 2.f;
}

float Camera::getAspectRatio() const
{
    return static_cast <float>(m_screenWidth) / m_screenHeight;
}

glm::vec2 Camera::getScale() const
{
    auto const ratio = getAspectRatio();
    
    glm::vec2 result;

    if (ratio > 1.f)
    {
        result = { 1.f / ratio, 1.f };
    }
    else
    {
        result = { 1.f, ratio };
    }

    return result;
}

END_NAMESPACE_SLEEP
