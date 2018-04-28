//
// Created by oleg on 20.02.18.
//

#include "TextureInfo.hpp"

using namespace BootstrapGL;

TextureInfo::TextureInfo(std::string filename,
                         GLenum target,
                         GLenum type,
                         bool flip_vertically)
        : filename(std::move(filename)),
          target(target),
          internal_format(GL_RGB),
          format(GL_RGB),
          type(type),
          flip_vertically(flip_vertically)
{}
