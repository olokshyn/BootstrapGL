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
    m_diffuse.load();
    m_specular.load();
    shader_program.set_uniform(name + ".diffuse", m_diffuse.raw_texture_number());
    shader_program.set_uniform(name + ".specular", m_specular.raw_texture_number());
    shader_program.set_uniform(name + ".shininess", m_shininess);
}
