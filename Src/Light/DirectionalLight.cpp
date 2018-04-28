//
// Created by oleg on 3/14/18.
//

#include "DirectionalLight.hpp"

#include "../Shader/ShaderProgram.hpp"

using namespace BootstrapGL;

DirectionalLight::DirectionalLight(const glm::vec3& direction,
                                   const glm::vec3& ambient,
                                   const glm::vec3& diffuse,
                                   const glm::vec3& specular)
        : m_direction(direction),
          m_ambient(ambient),
          m_diffuse(diffuse),
          m_specular(specular)
{}

glm::vec3& DirectionalLight::direction()
{
    return m_direction;
}

void DirectionalLight::set_light(ShaderProgram& shader_program,
                                 const std::string& name) const
{
    shader_program.set_uniform(name + ".direction", m_direction);
    shader_program.set_uniform(name + ".properties.ambient", m_ambient);
    shader_program.set_uniform(name + ".properties.diffuse", m_diffuse);
    shader_program.set_uniform(name + ".properties.specular", m_specular);
}
