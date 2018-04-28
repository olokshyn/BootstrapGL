//
// Created by oleg on 3/14/18.
//

#ifndef LIGHTNING_DIRECTIONALLIGHT_HPP
#define LIGHTNING_DIRECTIONALLIGHT_HPP

#include <string>

#include <glm/glm/glm.hpp>

namespace BootstrapGL
{

class ShaderProgram;

class DirectionalLight
{
public:
    DirectionalLight(const glm::vec3& direction,
                     const glm::vec3& ambient,
                     const glm::vec3& diffuse,
                     const glm::vec3& specular);

    glm::vec3& direction();

    void set_light(ShaderProgram& shader_program,
                   const std::string& name) const;

private:
    glm::vec3 m_direction;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
};

}

#endif //LIGHTNING_DIRECTIONALLIGHT_HPP
