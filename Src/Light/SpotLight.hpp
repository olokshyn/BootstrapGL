//
// Created by oleg on 3/16/18.
//

#ifndef LIGHTNING_SPOTLIGHT_HPP
#define LIGHTNING_SPOTLIGHT_HPP

#include <string>

#include <glm/glm/glm.hpp>

#include "PointLight.hpp"

namespace BootstrapGL
{

class ShaderProgram;

class SpotLight
{
public:
    explicit SpotLight(const PointLight& point_light,
                       const glm::vec3& direction,
                       float cut_off = glm::cos(glm::radians(12.5f)),
                       float outer_cut_off = glm::cos(glm::radians(17.5f)),
                       bool enabled = true);

    glm::vec3& position();
    glm::vec3& direction();

    void set_light(ShaderProgram& shader_program,
                   const std::string& name) const;

    bool is_enabled() const;
    void enable();
    void disable();
    void toggle();

private:
    PointLight m_point_light;
    glm::vec3 m_direction;
    float m_cut_off;
    float m_outer_cut_off;
    bool m_enabled;
};

}

#endif //LIGHTNING_SPOTLIGHT_HPP
