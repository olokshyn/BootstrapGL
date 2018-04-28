//
// Created by oleg on 3/24/18.
//

#include "Mesh.hpp"

#include "Shader/ShaderProgram.hpp"

using namespace BootstrapGL;

Mesh::Mesh(std::vector<Vertex>&& vertices,
           std::vector<unsigned int>&& indices,
           std::vector<Texture>&& diffuse_textures,
           std::vector<Texture>&& specular_textures)
        : m_vertices(std::move(vertices)),
          m_indices(std::move(indices)),
          m_diffuse_textures(std::move(diffuse_textures)),
          m_specular_textures(std::move(specular_textures)),
          m_vao([this](unsigned int vbo)
                {
                    glBufferData(GL_ARRAY_BUFFER,
                                 m_vertices.size() * sizeof(m_vertices[0]),
                                 m_vertices.data(),
                                 GL_STATIC_DRAW);
                },
                [this](unsigned int vao)
                {
                    glEnableVertexAttribArray(0);
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                                          sizeof(Vertex),
                                          reinterpret_cast<void*>(0));

                    glEnableVertexAttribArray(1);
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                                          sizeof(Vertex),
                                          reinterpret_cast<void*>(offsetof(Vertex, normal)));

                    glEnableVertexAttribArray(2);
                    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                                          sizeof(Vertex),
                                          reinterpret_cast<void*>(offsetof(Vertex, texture_coords)));
                },
                [this](unsigned int ebo)
                {
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                                 m_indices.size() * sizeof(m_indices[0]),
                                 m_indices.data(),
                                 GL_STATIC_DRAW);
                })
{
}

Mesh::Mesh(Mesh&& other)
        : m_vertices(std::move(other.m_vertices)),
          m_indices(std::move(other.m_indices)),
          m_diffuse_textures(std::move(other.m_diffuse_textures)),
          m_specular_textures(std::move(other.m_specular_textures)),
          m_vao(std::move(other.m_vao))
{
}

void Mesh::render(ShaderProgram& program)
{
    for (size_t i = 0; i != m_diffuse_textures.size(); ++i)
    {
        m_diffuse_textures[i].load();
        program.set_uniform("diffuse_textures[" + std::to_string(i) + "]",
                            m_diffuse_textures[i].raw_texture_number());
    }
    program.set_uniform("diffuse_textures_count", m_diffuse_textures.size());

    for (size_t i = 0; i != m_specular_textures.size(); ++i)
    {
        m_specular_textures[i].load();
        program.set_uniform("specular_textures[" + std::to_string(i) + "]",
                            m_specular_textures[i].raw_texture_number());
    }
    program.set_uniform("specular_textures_count", m_specular_textures.size());

    m_vao.use();
    glDrawElements(GL_TRIANGLES,
                   static_cast<int>(m_indices.size()),
                   GL_UNSIGNED_INT, 0);
}
