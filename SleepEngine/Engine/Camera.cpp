#include "stdafx.h"
#include "Camera.h"


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
    return { position.x / m_screenWidth, position.y / m_screenWidth };
}
