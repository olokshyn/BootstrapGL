//
// Created by oleg on 3/16/18.
//

#include "SpotLight.hpp"

#include "../Shader/ShaderProgram.hpp"

using namespace BootstrapGL;

SpotLight::SpotLight(const PointLight& point_light,
                     const glm::vec3& direction,
                     float cut_off,
                     float outer_cut_off,
                     bool enabled)
        : m_point_light(point_light),
          m_direction(direction),
          m_cut_off(cut_off),
          m_outer_cut_off(outer_cut_off),
          m_enabled(enabled)
{
}

glm::vec3& SpotLight::position()
{
    return m_point_light.position();
}

glm::vec3& SpotLight::direction()
{
    return m_direction;
}

void SpotLight::set_light(ShaderProgram& shader_program,
                          const std::string& name) const
{
    if (m_enabled)
    {
        m_point_light.set_light(shader_program, name + ".light");
        shader_program.set_uniform(name + ".direction", m_direction);
        shader_program.set_uniform(name + ".cut_off", m_cut_off);
        shader_program.set_uniform(name + ".outer_cut_off", m_outer_cut_off);
    }
    shader_program.set_uniform(name + ".enabled", m_enabled);
}

bool SpotLight::is_enabled() const
{
    return m_enabled;
}


void SpotLight::enable()
{
    m_enabled = true;
}

void SpotLight::disable()
{
    m_enabled = false;
}

void SpotLight::toggle()
{
    m_enabled = !m_enabled;
}
