// Copyright 2019, Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Camera
{
    FORBID_COPY_AND_MOVE(Camera)
public:
    Camera(size_t screenWidth, size_t screenHeight);

    void setScreenSize(size_t screenWidth, size_t screenHeight);
    glm::vec2 virtualPositionToNormalized(glm::vec2 position) const;
    glm::vec2 virtualSizeToNormalized(glm::vec2 size) const;
    float getAspectRatio() const;
    glm::vec2 getScale() const;

    GETTER(getScreenWidth, m_screenWidth)
    GETTER(getScreenHeight, m_screenHeight)

    glm::vec2 getScreenSize() const { return { m_screenWidth, m_screenHeight }; }

private:
    size_t m_screenWidth;
    size_t m_screenHeight;
    glm::uvec2 m_virtualScreenSize;
};

END_NAMESPACE_SLEEP
