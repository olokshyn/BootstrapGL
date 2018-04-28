//
// Created by oleg on 27.02.18.
//

#include "VertexBufferHandle.hpp"

#include <algorithm>
#include <stdexcept>

#include <glad/glad.h>

using namespace BootstrapGL;

VertexBufferHandle::VertexBufferHandle(int count)
        : m_count(count)
{
    if (m_count <= 0)
    {
        throw std::runtime_error("Invaild count parameter");
    }
    glGenBuffers(m_count, &m_vbo);
}

VertexBufferHandle::~VertexBufferHandle()
{
    if (m_vbo)
    {
        glDeleteBuffers(m_count, &m_vbo);
    }
}

VertexBufferHandle::VertexBufferHandle(VertexBufferHandle&& other)
        : m_vbo(other.m_vbo)
{
    other.m_vbo = 0;
}

VertexBufferHandle& VertexBufferHandle::operator=(VertexBufferHandle other)
{
    std::swap(m_vbo, other.m_vbo);
    return *this;
}

VertexBufferHandle::operator unsigned int()
{
    return m_vbo;
}
