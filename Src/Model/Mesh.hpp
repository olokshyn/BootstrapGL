//
// Created by oleg on 3/24/18.
//

#ifndef MODELS_MESH_HPP
#define MODELS_MESH_HPP

#include <vector>

#include "Texture/Texture.hpp"
#include "VAO/Vertex.hpp"
#include "VAO/VertexArray.hpp"

namespace BootstrapGL
{

class ShaderProgram;

class Mesh
{
public:
    Mesh(std::vector<Vertex>&& vertices,
         std::vector<unsigned int>&& indices,
         std::vector<Texture>&& diffuse_textures,
         std::vector<Texture>&& specular_textures);

    Mesh(Mesh&& other);
    Mesh& operator=(const Mesh& other) = delete;

    void render(ShaderProgram& program);

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    std::vector<Texture> m_diffuse_textures;
    std::vector<Texture> m_specular_textures;
    VertexArray m_vao;
};

}

#endif //MODELS_MESH_HPP
