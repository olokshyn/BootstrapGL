//
// Created by oleg on 03.03.18.
//

#include "Material.hpp"

#include "Shader/ShaderProgram.hpp"

using namespace BootstrapGL;

Material::Material(Texture&& diffuse,
                   Texture&& specular,
                   float shininess)
        : m_diffuse(std::move(diffuse)),
          m_specular(std::move(specular)),
          m_shininess(shininess)
{
}

void Material::set_material(ShaderProgram& shader_program,
                            const std::string& name) const
{
    m_diffuse.set_texture(shader_program, name + ".diffuse");
    m_specular.set_texture(shader_program, name + ".specular");
    shader_program.set_uniform(name + ".shininess", m_shininess);
}
