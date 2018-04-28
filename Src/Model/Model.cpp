//
// Created by oleg on 3/24/18.
//

#include "Model.hpp"

#include <stdexcept>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

using namespace BootstrapGL;

Model::Model(const std::string& path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.c_str(),
                                             aiProcess_Triangulate
                                             | aiProcess_FlipUVs
                                             | aiProcess_CalcTangentSpace);
    if (!scene
        || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
        || !scene->mRootNode)
    {
        throw std::runtime_error("Failed to load model " + path);
    }
    m_meshes.reserve(scene->mNumMeshes);

    std::string directory;
    size_t delimiter = path.find_last_of('/');
    if (delimiter != std::string::npos)
    {
        directory = path.substr(0, delimiter + 1);
    }
    else
    {
        directory = "./";
    }

    process_node(scene->mRootNode, scene, directory);
}

void Model::render(ShaderProgram& program)
{
    for (auto& mesh : m_meshes)
    {
        mesh.render(program);
    }
}

void Model::process_node(aiNode* node, const aiScene* scene, const std::string& directory)
{
    for (unsigned int i = 0; i != node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(process_mesh(mesh, scene, directory));
    }
    for (unsigned int i = 0; i != node->mNumChildren; ++i)
    {
        process_node(node->mChildren[i], scene, directory);
    }
}

Mesh Model::process_mesh(aiMesh* mesh, const aiScene* scene, const std::string& directory)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> diffuse_textures;
    std::vector<Texture> specular_textures;

    vertices.reserve(mesh->mNumVertices);
    for (unsigned int i = 0; i != mesh->mNumVertices; ++i)
    {
        vertices.emplace_back(
                glm::vec3(mesh->mVertices[i].x,
                          mesh->mVertices[i].y,
                          mesh->mVertices[i].z),
                glm::vec3(mesh->mNormals[i].x,
                          mesh->mNormals[i].y,
                          mesh->mNormals[i].z),
                mesh->mTextureCoords[0] ? glm::vec2(mesh->mTextureCoords[0][i].x,
                                                    mesh->mTextureCoords[0][i].y)
                                        : glm::vec2(0.0f));
    }

    size_t indices_count = 0;
    for (unsigned int i = 0; i != mesh->mNumFaces; ++i)
    {
        indices_count += mesh->mFaces[i].mNumIndices;
    }
    indices.reserve(indices_count);
    for (unsigned int i = 0; i != mesh->mNumFaces; ++i)
    {
        const aiFace& face = mesh->mFaces[i];
        for (unsigned int j = 0; j != face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        size_t next_texture_number = 0;
        load_textures(material, aiTextureType_DIFFUSE, directory,
                      diffuse_textures, next_texture_number);
        load_textures(material, aiTextureType_SPECULAR, directory,
                      specular_textures, next_texture_number);
    }

    return Mesh(std::move(vertices),
                std::move(indices),
                std::move(diffuse_textures),
                std::move(specular_textures));
}

void Model::load_textures(aiMaterial* material,
                          aiTextureType texture_type,
                          const std::string& directory,
                          std::vector<Texture>& textures,
                          size_t& next_texture_number)
{
    unsigned int textures_count = material->GetTextureCount(texture_type);
    textures.reserve(textures_count);
    for (unsigned int i = 0; i != textures_count; ++i)
    {
        aiString str;
        material->GetTexture(texture_type, i, &str);
        TextureInfo info(directory + str.C_Str());
        info.flip_vertically = false;
        textures.emplace_back(info, next_texture_number++);
    }
}
