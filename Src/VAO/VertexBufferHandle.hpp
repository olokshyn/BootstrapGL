//
// Created by oleg on 27.02.18.
//

#ifndef LIGHTNING_VERTEXBUFFERHANDLE_HPP
#define LIGHTNING_VERTEXBUFFERHANDLE_HPP

namespace BootstrapGL
{

class VertexBufferHandle
{
public:
    explicit VertexBufferHandle(int count = 1);
    ~VertexBufferHandle();

    VertexBufferHandle(VertexBufferHandle&& other);

    VertexBufferHandle& operator=(VertexBufferHandle other);

    operator unsigned int();

    int count() const
    { return m_count; }

private:
    unsigned int m_vbo;
    int m_count;
};

}

#endif //LIGHTNING_VERTEXBUFFERHANDLE_HPP
