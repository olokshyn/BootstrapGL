//
// Created by oleg on 19.02.18.
//

#include "TextureHandle.hpp"

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

using namespace BootstrapGL;

TextureHandle::TextureHandle(TextureInfo info)
        : m_info(std::move(info))
{
    stbi_set_flip_vertically_on_load(m_info.flip_vertically);
    m_data = stbi_load(info.filename.c_str(), &m_width, &m_height,
                       &m_number_of_channels, 0);
    if (!m_data)
    {
        throw std::runtime_error("Failed to load texture " + m_info.filename);
    }

    switch (m_number_of_channels)
    {
    case 1:
        m_info.internal_format = GL_RED;
        m_info.format = GL_RED;
        break;
    case 3:
        m_info.internal_format = GL_RGB;
        m_info.format = GL_RGB;
        break;
    case 4:
        m_info.internal_format = GL_RGBA;
        m_info.format = GL_RGBA;
        break;
    }
}

TextureHandle::~TextureHandle()
{
    if (m_data)
    {
        stbi_image_free(m_data);
    }
}

TextureHandle::TextureHandle(TextureHandle&& other)
    : m_info(other.m_info),
      m_data(other.m_data),
      m_width(other.m_width),
      m_height(other.m_height),
      m_number_of_channels(other.m_number_of_channels)
{
    other.m_data = nullptr;
    other.m_width = 0;
    other.m_height = 0;
    other.m_number_of_channels = 0;
}

void TextureHandle::set_texture() const
{
    if (m_data)
    {
        glTexImage2D(m_info.target, 0, m_info.internal_format, m_width, m_height,
                     0, m_info.format, m_info.type, m_data);
    }
}

void TextureHandle::create_mipmap()
{
    if (m_data)
    {
        set_texture();
        glGenerateMipmap(m_info.target);
    }
}
