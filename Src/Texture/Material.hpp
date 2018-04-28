//
// Created by oleg on 03.03.18.
//

#ifndef LIGHTNING_MATERIAL_HPP
#define LIGHTNING_MATERIAL_HPP

#include <string>
#include <iostream>

#include <glm/glm/glm.hpp>

#include "Texture.hpp"

namespace BootstrapGL
{

class ShaderProgram;

class Material
{
public:
    Material(Texture&& diffuse,
             Texture&& specular,
             float shininess = 32.0f);

    void set_material(ShaderProgram& shader_program,
                      const std::string& name) const;

private:
    Texture m_diffuse;
    Texture m_specular;
    float m_shininess;
};

}

#endif //LIGHTNING_MATERIAL_HPP
