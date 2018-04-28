//
// Created by oleg on 16.02.18.
//

#ifndef SHADERS_SHADERPROGRAM_HPP
#define SHADERS_SHADERPROGRAM_HPP

#include <string>
#include <unordered_map>
#include <glm/glm/glm.hpp>

namespace BootstrapGL
{

class ShaderProgram
{
public:
    ShaderProgram(const std::string& vertex_shader_filename,
                  const std::string& fragment_shader_filename);

    void use();
    void unuse();

    void set_uniform(const std::string& name, int value);
    void set_uniform(const std::string& name, size_t value);
    void set_uniform(const std::string& name, float value);
    void set_uniform(const std::string& name, const glm::vec3& value);
    void set_uniform(const std::string& name, const glm::mat4& value);

private:
    class ProgramHandle
    {
    public:
        explicit ProgramHandle(unsigned int program_id = 0)
                : m_program_id(program_id)
        {}

        ~ProgramHandle();

        ProgramHandle(const ProgramHandle& other) = delete;

        ProgramHandle& operator=(const ProgramHandle& other) = delete;

        operator unsigned int() const
        { return m_program_id; }

        operator bool() const
        { return m_program_id > 0; }

    private:
        unsigned int m_program_id;
    };

private:
    int find_uniform(const std::string& name);

private:
    ProgramHandle m_program;
    bool m_used;
    std::unordered_map<std::string, int> m_cached_uniforms;
};

}

#endif //SHADERS_SHADERPROGRAM_HPP
