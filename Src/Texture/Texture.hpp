//
// Created by oleg on 19.02.18.
//

#ifndef TEXTURES_TEXTURE_HPP
#define TEXTURES_TEXTURE_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TextureInfo.hpp"

namespace BootstrapGL
{

class ShaderProgram;

class Texture
{
public:
    explicit Texture(TextureInfo info, size_t texture_number = 0);
    ~Texture();

    Texture(Texture&& other);

    operator unsigned int() const
    { return m_texture_id; }

    void load() const;

    GLenum texture_number() const;
    size_t raw_texture_number() const;

    void set_texture(ShaderProgram& shader_program,
                     const std::string& name) const;

private:
    GLenum m_type;
    size_t m_texture_number;
    unsigned int m_texture_id;
};

}

#endif //TEXTURES_TEXTURE_HPP
