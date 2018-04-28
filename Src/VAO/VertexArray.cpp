//
// Created by oleg on 01.03.18.
//

#include "VertexArray.hpp"

#include <glad/glad.h>

using namespace BootstrapGL;

VertexArray::VertexArray(const std::function<void(unsigned int)>& vertex_buffer_initializer,
                         const std::function<void(unsigned int)>& array_object_initializer,
                         const std::function<void(unsigned int)>& element_buffer_initializer)
        : m_ebo(nullptr)
{
    use();
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    vertex_buffer_initializer(m_vbo);
    if (element_buffer_initializer)
    {
        m_ebo.reset(new VertexBufferHandle());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_ebo);
        element_buffer_initializer(*m_ebo);
    }
    array_object_initializer(m_vao);
}

VertexArray::VertexArray(VertexArray&& other)
        : m_vao(std::move(other.m_vao)),
          m_vbo(std::move(other.m_vbo)),
          m_ebo(std::move(other.m_ebo))
{
}

void VertexArray::use()
{
    glBindVertexArray(m_vao);
}
