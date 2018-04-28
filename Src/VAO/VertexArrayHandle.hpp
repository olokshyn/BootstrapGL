//
// Created by oleg on 27.02.18.
//

#ifndef LIGHTNING_VERTEXARRAYHANDLE_HPP
#define LIGHTNING_VERTEXARRAYHANDLE_HPP

namespace BootstrapGL
{

class VertexArrayHandle
{
public:
    explicit VertexArrayHandle(int count = 1);
    ~VertexArrayHandle();

    VertexArrayHandle(VertexArrayHandle&& other);
    VertexArrayHandle& operator=(VertexArrayHandle other);

    operator unsigned int();

    int count() const
    { return m_count; }

private:
    unsigned int m_vao;
    int m_count;
};

}

#endif //LIGHTNING_VERTEXARRAYHANDLE_HPP
