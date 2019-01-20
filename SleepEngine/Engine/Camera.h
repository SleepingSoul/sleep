#pragma once

class Camera
{
public:
    Camera(size_t screenWidth, size_t screenHeight);

    void setScreenSize(size_t screenWidth, size_t screenHeight);
    glm::vec2 virtualPositionToNormalized(glm::vec2 position) const;

private:
    size_t m_screenWidth;
    size_t m_screenHeight;
};
