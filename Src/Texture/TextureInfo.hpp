//
// Created by oleg on 20.02.18.
//

#ifndef TRANSFORMATIONS_TEXTUREINFO_HPP
#define TRANSFORMATIONS_TEXTUREINFO_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace BootstrapGL
{

struct TextureInfo
{
    TextureInfo(std::string filename,
                GLenum target = GL_TEXTURE_2D,
                GLenum type = GL_UNSIGNED_BYTE,
                bool flip_vertically = true);

    const std::string filename;
    const GLenum target;
    GLenum internal_format;
    GLenum format;
    GLenum type;
    bool flip_vertically;
};

}

#endif //TRANSFORMATIONS_TEXTUREINFO_HPP
