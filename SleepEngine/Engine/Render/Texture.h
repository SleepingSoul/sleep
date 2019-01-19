#pragma once

class Texture final
{
public:
    using TextureIDType = GLuint;

    Texture(char const* path);
    ~Texture();

    TextureIDType getID() const { return m_id; }
    size_t getWidth() const { return m_width; }
    size_t getHeight() const { return m_height; }
    size_t getChannelsNumber() const { return m_channelsNumber; }

    glm::vec2 getTopLeftUV() const { return m_topLeftUV; }
    void setTopLeftUV(glm::vec2 const uv) { m_topLeftUV = uv; }

    glm::vec2 getDownRightUV() const { return m_downRightUV; }
    void setDownRightUV(glm::vec2 const uv) { m_downRightUV = uv; }

    void setUV(float topLeftX, float topLeftY, float downRightX, float downRightY);

private:
    GLenum channelsNumberToFormat(int channelsNumber) const;

    unsigned char* m_data;
    TextureIDType m_id;
    size_t m_width;
    size_t m_height;
    size_t m_channelsNumber;
    glm::vec2 m_topLeftUV;
    glm::vec2 m_downRightUV;
};
