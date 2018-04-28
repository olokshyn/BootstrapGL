//
// Created by oleg on 03.03.18.
//

#ifndef LIGHTNING_LIGHT_HPP
#define LIGHTNING_LIGHT_HPP

#include <string>

#include <glm/glm/glm.hpp>

namespace BootstrapGL
{

class ShaderProgram;

class PointLight
{
public:
    PointLight(const glm::vec3& position,
               const glm::vec3& ambient,
               const glm::vec3& diffuse,
               const glm::vec3& specular,
               float constant = 1.0f,  // Distance: 32
               float linear = 0.14f,
               float quadratic = 0.07f);

    glm::vec3& position();

    void set_light(ShaderProgram& shader_program,
                   const std::string& name) const;

private:
    glm::vec3 m_position;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    float m_constant;
    float m_linear;
    float m_quadratic;
};

}

#endif //LIGHTNING_LIGHT_HPP
