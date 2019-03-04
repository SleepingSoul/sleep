// Copyright 2019 Tihran Katolikian

#pragma once

BeginNamespaceSleep

class Texture final
{
public:
    using TextureIDType = GLuint;

    Texture(char const* path) noexcept(true);
    ~Texture();

    TextureIDType getID() const { return m_id; }
    size_t getWidth() const { return m_width; }
    size_t getHeight() const { return m_height; }
    size_t getChannelsNumber() const { return m_channelsNumber; }
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

EndNamespaceSleep
