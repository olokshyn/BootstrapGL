//
// Created by oleg on 19.02.18.
//

#include "Texture.hpp"

#include <stdexcept>

#include "TextureHandle.hpp"
#include "Shader/ShaderProgram.hpp"

using namespace BootstrapGL;

Texture::Texture(TextureInfo info, size_t texture_number)
        : m_type(info.target),
          m_texture_number(texture_number)
{
//    if (texture_number >= GL_MAX_TEXTURE_IMAGE_UNITS)
//    {
//        throw std::runtime_error("Texture number is too huge");
//    }

    TextureHandle texture_handle(info);

    glGenTextures(1, &m_texture_id);
    glBindTexture(m_type, m_texture_id);

    texture_handle.create_mipmap();

    glTexParameteri(m_type, GL_TEXTURE_WRAP_S, 
                    texture_handle.info().format == GL_RGBA
                    ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(m_type, GL_TEXTURE_WRAP_T,
                    texture_handle.info().format == GL_RGBA
                    ? GL_CLAMP_TO_EDGE : GL_REPEAT);
    glTexParameteri(m_type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(m_type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
    if (m_texture_id)
    {
        glDeleteTextures(1, &m_texture_id);
    }
}

Texture::Texture(Texture&& other)
    : m_type(other.m_type),
      m_texture_number(other.m_texture_number),
      m_texture_id(other.m_texture_id)
{
    other.m_type = 0;
    other.m_texture_number = 0;
    other.m_texture_id = 0;
}

void Texture::load() const
{
    if (m_texture_id)
    {
        glActiveTexture(texture_number());
        glBindTexture(m_type, m_texture_id);
    }
}

GLenum Texture::texture_number() const
{
    return static_cast<GLenum>(GL_TEXTURE0 + m_texture_number);
}

size_t Texture::raw_texture_number() const
{
    return m_texture_number;
}

void Texture::set_texture(ShaderProgram& shader_program,
                          const std::string& name) const
{
    load();
    shader_program.set_uniform(name, m_texture_number);
}

