//
// Created by oleg on 3/24/18.
//

#ifndef MODELS_MODEL_HPP
#define MODELS_MODEL_HPP

#include <string>
#include <vector>

#include <assimp/scene.h>

#include "Mesh.hpp"

namespace BootstrapGL
{

class ShaderProgram;

class Model
{
public:
    explicit Model(const std::string& path);
    void render(ShaderProgram& program);

private:
    void process_node(aiNode* node, const aiScene* scene, const std::string& directory);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene, const std::string& directory);
    void load_textures(aiMaterial* material,
                       aiTextureType texture_type,
                       const std::string& directory,
                       std::vector<Texture>& textures,
                       size_t& next_texture_number);

private:
    std::vector<Mesh> m_meshes;

};

}

#endif //MODELS_MODEL_HPP
