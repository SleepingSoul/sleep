#include "stdafx.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


Texture::Texture(char const* path)
{
    int width, height, channelsNumber;
    stbi_set_flip_vertically_on_load(true);
    m_data = stbi_load(path, &width, &height, &channelsNumber, 0);
    assertion(width > 0 && height > 0 && channelsNumber > 0, "Failed to properly read texture.");

    m_width = static_cast <size_t>(width);
    m_height = static_cast <size_t>(height);
    m_channelsNumber = static_cast <size_t>(channelsNumber);

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    auto const format = channelsNumberToFormat(channelsNumber);
    glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
    stbi_image_free(m_data);
}

GLenum Texture::channelsNumberToFormat(int const channelsNumber) const
{
    GLenum result = GL_NONE;
    switch (channelsNumber)
    {
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
