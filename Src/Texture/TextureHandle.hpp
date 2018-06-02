//
// Created by oleg on 19.02.18.
//

#ifndef TEXTURES_TEXTUREHANDLE_HPP
#define TEXTURES_TEXTUREHANDLE_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TextureInfo.hpp"

namespace BootstrapGL
{

class TextureHandle
{
public:
    explicit TextureHandle(BootstrapGL::TextureInfo info);
    ~TextureHandle();

    TextureHandle(TextureHandle&& other);

    void set_texture() const;

    void create_mipmap();

    int width() const
    { return m_width; }

    int height() const
    { return m_height; }

    int number_of_channels() const
    { return m_number_of_channels; }

    const TextureInfo& info() const
    { return m_info; }

private:
    TextureInfo m_info;
    unsigned char* m_data;
    int m_width;
    int m_height;
    int m_number_of_channels;
};

}

#endif //TEXTURES_TEXTUREHANDLE_HPP
