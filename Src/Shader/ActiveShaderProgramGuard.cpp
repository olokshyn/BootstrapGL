//
// Created by oleg on 01.03.18.
//

#include "ActiveShaderProgramGuard.hpp"

#include <algorithm>

using namespace BootstrapGL;

ActiveShaderProgramGuard::ActiveShaderProgramGuard(ShaderProgram* program)
    : m_program(program)
{
    m_program->use();
}

ActiveShaderProgramGuard::~ActiveShaderProgramGuard()
{
    if (m_program)
    {
        m_program->unuse();
    }
}

ActiveShaderProgramGuard::ActiveShaderProgramGuard(ActiveShaderProgramGuard&& other)
    : m_program(other.m_program)
{
    other.m_program = nullptr;
}

ActiveShaderProgramGuard& ActiveShaderProgramGuard::operator=(ActiveShaderProgramGuard other)
{
    std::swap(m_program, other.m_program);
    return *this;
}

ActiveShaderProgramGuard& ActiveShaderProgramGuard::operator=(ShaderProgram& program)
{
    ActiveShaderProgramGuard temp(std::move(*this));
    m_program = &program;
    m_program->use();
    return *this;
}
