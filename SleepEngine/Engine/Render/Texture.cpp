#include "stdafx.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


Texture::Texture(char const* path) noexcept(true)
{
    int width, height, channelsNumber;
    m_data = stbi_load(path, &width, &height, &channelsNumber, 0);
    assertion(width > 0 && height > 0 && channelsNumber > 0, "Failed to properly read texture.");

    m_width = static_cast <size_t>(width);
    m_height = static_cast <size_t>(height);
    m_channelsNumber = static_cast <size_t>(channelsNumber);

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    stbi_image_free(m_data);
}

void Texture::loadToGPU()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
    if (m_data)
    {
        auto const format = channelsNumberToFormat(m_channelsNumber);
        glTexImage2D(GL_TEXTURE_2D, 0, format, static_cast <GLsizei>(m_width), static_cast <GLsizei>(m_height),
            0, format, GL_UNSIGNED_BYTE, m_data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLenum Texture::channelsNumberToFormat(int const channelsNumber) const
{
    GLenum result = GL_NONE;
    switch (channelsNumber)
    {
    case 1:
        result = GL_RED;
        break;
    case 3:
        result = GL_RGB;
        break;
    case 4:
        result = GL_RGBA;
        break;
    default:
        assertion(false, "Texture is not supported. Cannot find format for it's channels number.");
    }

    return result;
}
