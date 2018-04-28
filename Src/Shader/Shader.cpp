//
// Created by oleg on 16.02.18.
//

#include "Shader.hpp"

#include <memory>
#include <fstream>
#include <iterator>
#include <stdexcept>

#include <glad/glad.h>

using namespace BootstrapGL;

Shader::Shader(unsigned int shader_type, const std::string& filename)
        : m_shader(glCreateShader(shader_type))
{
    if (!m_shader)
    {
        throw std::runtime_error("Failed to create shader program");
    }

    std::string shader_source = load_shader_source(filename);
    const char* shader_source_str = shader_source.c_str();
    glShaderSource(m_shader, 1, &shader_source_str, nullptr);

    glCompileShader(m_shader);

    int compilation_succeeded = 0;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &compilation_succeeded);
    if (!compilation_succeeded)
    {
        char info_log[512];
        glGetShaderInfoLog(m_shader, sizeof(info_log), NULL, info_log);
        throw std::runtime_error("Failed to compile shader: " + std::string(info_log));
    }
}

Shader::ShaderHandle::~ShaderHandle()
{
    if (m_shader_id)
    {
        glDeleteShader(m_shader_id);
    }
}

std::string Shader::load_shader_source(const std::string& filename)
{
    std::ifstream shader_file;
    shader_file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    shader_file.open(filename);
    return std::string(std::istreambuf_iterator<char>(shader_file),
                       std::istreambuf_iterator<char>());
}
