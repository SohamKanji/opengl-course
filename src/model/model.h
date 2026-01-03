#pragma once

#include <vector>
#include <string>
#include <filesystem>

class Mesh;
class Texture;
class aiNode;
class aiScene;
class aiMesh;

class Model
{

public:

    Model(const std::string& file_path);
    ~Model();

    void loadModel(const std::string& file_path);
    void renderModel();
    void clearModel();

private:

    void loadNode(aiNode* node, const aiScene* scene);
    void loadMesh(aiMesh* mesh, const aiScene* scene);
    void loadMaterial(const aiScene* scene);

private:

    std::vector<Mesh*> m_meshes;
    std::vector<Texture*> m_textures;
    std::vector<int> m_mesh_to_texture;
    std::filesystem::path m_directory;
};