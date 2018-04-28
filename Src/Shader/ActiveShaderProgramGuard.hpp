//
// Created by oleg on 01.03.18.
//

#ifndef LIGHTNING_ACTIVESHADERPROGRAMGUARD_HPP
#define LIGHTNING_ACTIVESHADERPROGRAMGUARD_HPP

#include "ShaderProgram.hpp"

namespace BootstrapGL
{

class ActiveShaderProgramGuard
{
public:
    explicit ActiveShaderProgramGuard(ShaderProgram* program = nullptr);
    ~ActiveShaderProgramGuard();

    ActiveShaderProgramGuard(ActiveShaderProgramGuard&& other);
    ActiveShaderProgramGuard& operator=(ActiveShaderProgramGuard other);

    ActiveShaderProgramGuard& operator=(ShaderProgram& program);

private:
    ShaderProgram* m_program;
};

}

#endif //LIGHTNING_ACTIVESHADERPROGRAMGUARD_HPP
