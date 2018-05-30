//
// Created by oleg on 16.02.18.
//

#include "ShaderProgram.hpp"

#include <stdexcept>

#include <glad/glad.h>
#include <glm/glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

using namespace BootstrapGL;

ShaderProgram::ShaderProgram(
        const std::string& vertex_shader_filename,
        const std::string& fragment_shader_filename)

        : m_program(glCreateProgram()),
          m_used(false)
{
    if (!m_program)
    {
        throw std::runtime_error("Failed to create shader program");
    }

    Shader vertex_shader(GL_VERTEX_SHADER, vertex_shader_filename);
    Shader fragment_shader(GL_FRAGMENT_SHADER, fragment_shader_filename);

    glAttachShader(m_program, vertex_shader);
    glAttachShader(m_program, fragment_shader);

    glLinkProgram(m_program);

    int link_succeeded = 0;
    glGetProgramiv(m_program, GL_LINK_STATUS, &link_succeeded);
    if (!link_succeeded)
    {
        char info_log[512];
        glGetProgramInfoLog(m_program, sizeof(info_log), NULL, info_log);
        throw std::runtime_error("Failed to link shader program: " + std::string(info_log));
    }
}

void ShaderProgram::use()
{
    glUseProgram(m_program);
    m_used = true;
}

void ShaderProgram::unuse()
{
    m_used = false;
}

void ShaderProgram::set_uniform(const std::string& name, int value)
{
    int uniform = find_uniform(name);
    glUniform1i(uniform, value);
}

void ShaderProgram::set_uniform(const std::string& name, unsigned int value)
{
    int uniform = find_uniform(name);
    // FIXME: glUniform1ui fails to set sampler2D value
    glUniform1i(uniform, static_cast<int>(value));
}

void ShaderProgram::set_uniform(const std::string& name, size_t value)
{
    int uniform = find_uniform(name);
    // FIXME: glUniform1ui fails to set sampler2D value
    glUniform1i(uniform, static_cast<int>(value));
}

void ShaderProgram::set_uniform(const std::string& name, float value)
{
    int uniform = find_uniform(name);
    glUniform1f(uniform, value);
}

void ShaderProgram::set_uniform(const std::string& name, const glm::vec3& value)
{
    int uniform = find_uniform(name);
    glUniform3fv(uniform, 1, glm::value_ptr(value));
}

void ShaderProgram::set_uniform(const std::string& name, const glm::mat4& value)
{
    int uniform = find_uniform(name);
    glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(value));
}

ShaderProgram::ProgramHandle::~ProgramHandle()
{
    if (m_program_id)
    {
        glDeleteProgram(m_program_id);
    }
}

int ShaderProgram::find_uniform(const std::string& name)
{
    if (!m_used)
    {
        throw std::runtime_error("Shader is not used");
    }
    auto info = m_cached_uniforms.insert({name, -1});
    if (info.second || info.first->second == -1)
    {
        info.first->second = glGetUniformLocation(m_program, name.c_str());
    }
    if (info.first->second == -1)
    {
        throw std::runtime_error("Failed to find uniform " + name);
    }
    return info.first->second;
}
