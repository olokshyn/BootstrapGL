//
// Created by oleg on 01.03.18.
//

#ifndef LIGHTNING_VERTEXARRAY_HPP
#define LIGHTNING_VERTEXARRAY_HPP

#include <memory>
#include <functional>

#include "VertexArrayHandle.hpp"
#include "VertexBufferHandle.hpp"

namespace BootstrapGL
{

class VertexArray
{
public:
    VertexArray(const std::function<void(unsigned int)>& vertex_buffer_initializer,
                const std::function<void(unsigned int)>& array_object_initializer,
                const std::function<void(unsigned int)>& element_buffer_initializer = {});

    VertexArray(VertexArray&& other);
    VertexArray& operator=(const VertexArray& other) = delete;

    void use();

private:
    VertexArrayHandle m_vao;
    VertexBufferHandle m_vbo;
    std::unique_ptr<VertexBufferHandle> m_ebo;
};

}

#endif //LIGHTNING_VERTEXARRAY_HPP
