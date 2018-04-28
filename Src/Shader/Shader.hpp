//
// Created by oleg on 16.02.18.
//

#ifndef SHADERS_SHADER_HPP
#define SHADERS_SHADER_HPP

#include <string>

namespace BootstrapGL
{

class Shader
{
public:
    explicit Shader(unsigned int shader_type, const std::string& filename);

    operator unsigned int() const
    { return m_shader; }

private:
    class ShaderHandle
    {
    public:
        explicit ShaderHandle(unsigned int shader_id = 0)
                : m_shader_id(shader_id)
        {}

        ~ShaderHandle();

        ShaderHandle(const ShaderHandle& other) = delete;

        ShaderHandle& operator=(const ShaderHandle& other) = delete;

        operator unsigned int() const
        { return m_shader_id; }

        operator bool() const
        { return m_shader_id > 0; }

    private:
        unsigned int m_shader_id;
    };

private:
    static std::string load_shader_source(const std::string& filename);

private:
    ShaderHandle m_shader;
};

}

#endif //SHADERS_SHADER_HPP
