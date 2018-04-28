//
// Created by oleg on 03.03.18.
//

#include "PointLight.hpp"

#include "../Shader/ShaderProgram.hpp"

using namespace BootstrapGL;

PointLight::PointLight(const glm::vec3& position,
                       const glm::vec3& ambient,
                       const glm::vec3& diffuse,
                       const glm::vec3& specular,
                       float constant,
                       float linear,
                       float quadratic)
        : m_position(position),
          m_ambient(ambient),
          m_diffuse(diffuse),
          m_specular(specular),
          m_constant(constant),
          m_linear(linear),
          m_quadratic(quadratic)
{

}

glm::vec3& PointLight::position()
{
    return m_position;
}

void PointLight::set_light(ShaderProgram& shader_program,
                           const std::string& name) const
{
    shader_program.set_uniform(name + ".position", m_position);
    shader_program.set_uniform(name + ".properties.ambient", m_ambient);
    shader_program.set_uniform(name + ".properties.diffuse", m_diffuse);
    shader_program.set_uniform(name + ".properties.specular", m_specular);
    shader_program.set_uniform(name + ".constant", m_constant);
    shader_program.set_uniform(name + ".linear", m_linear);
    shader_program.set_uniform(name + ".quadratic", m_quadratic);

}
