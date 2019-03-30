// Copyright 2019 Tihran Katolikian

#pragma once

BEGIN_NAMESPACE_SLEEP

class Texture final
{
public:
    using TextureIDType = GLuint;

    Texture(char const* path) noexcept(true);
    ~Texture();

    GETTER(getID, m_id)
    GETTER(getWidth, m_width)
    GETTER(getHeight, m_height)
    GETTER(getChannelsNumber, m_channelsNumber)

    glm::vec2 getSize() const { return { m_width, m_height }; }

    void loadToGPU();
    void unloadFromGPU();
    bool isInGPU() const { return m_isInGPU; }

    std::string_view getPath() const { return m_path; }

private:
    GLenum channelsNumberToFormat(int channelsNumber) const;

    unsigned char* m_data;
    TextureIDType m_id;
    size_t m_width;
    size_t m_height;
    size_t m_channelsNumber;

    std::string m_path;
    bool m_isInGPU;
};

END_NAMESPACE_SLEEP
