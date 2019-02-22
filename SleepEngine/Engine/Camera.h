// Copyright 2019, Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Camera
{
    ForbidCopyAndMove(Camera)
public:
    Camera(size_t screenWidth, size_t screenHeight);

    void setScreenSize(size_t screenWidth, size_t screenHeight);
    glm::vec2 virtualPositionToNormalized(glm::vec2 position) const;
    glm::vec2 virtualSizeToNormalized(glm::vec2 size) const;
    float getAspectRatio() const;
    glm::vec2 getScale() const;
    size_t getScreenWidth() const { return m_screenWidth; }
    size_t getScreenHeight() const { return m_screenHeight; }
    glm::vec2 getScreenSize() const { return { m_screenWidth, m_screenHeight }; }

private:
    size_t m_screenWidth;
    size_t m_screenHeight;
    glm::uvec2 m_virtualScreenSize;
};

EndNamespaceSleep
