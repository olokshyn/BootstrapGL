//
// Created by oleg on 27.02.18.
//

#include "VertexArrayHandle.hpp"

#include <algorithm>
#include <stdexcept>

#include <glad/glad.h>

using namespace BootstrapGL;

VertexArrayHandle::VertexArrayHandle(int count)
        : m_count(count)
{
    if (m_count <= 0)
    {
        throw std::runtime_error("Invaild count parameter");
    }
    glGenVertexArrays(m_count, &m_vao);
}

VertexArrayHandle::~VertexArrayHandle()
{
    if (m_vao)
    {
        glDeleteVertexArrays(m_count, &m_vao);
    }
}

VertexArrayHandle::VertexArrayHandle(VertexArrayHandle&& other)
        : m_vao(other.m_vao)
{
    other.m_vao = 0;
}

VertexArrayHandle& VertexArrayHandle::operator=(VertexArrayHandle other)
{
    std::swap(m_vao, other.m_vao);
    return *this;
}

VertexArrayHandle::operator unsigned int()
{
    return m_vao;
}
