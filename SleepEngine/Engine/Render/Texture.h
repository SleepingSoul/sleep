#pragma once

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
    void loadToGPU();

private:
    GLenum channelsNumberToFormat(int channelsNumber) const;

    unsigned char* m_data;
    TextureIDType m_id;
    size_t m_width;
    size_t m_height;
    size_t m_channelsNumber;
};
