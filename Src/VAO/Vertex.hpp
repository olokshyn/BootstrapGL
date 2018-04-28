//
// Created by oleg on 3/24/18.
//

#ifndef MODELS_VERTEX_HPP
#define MODELS_VERTEX_HPP

#include <glm/glm/glm.hpp>

namespace BootstrapGL
{

struct Vertex
{
    Vertex(const glm::vec3& position,
           const glm::vec3& normal,
           const glm::vec2& texture_coords = glm::vec2())
            : position(position),
              normal(normal),
              texture_coords(texture_coords)
    {}

    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texture_coords;
};

}

#endif //MODELS_VERTEX_HPP
