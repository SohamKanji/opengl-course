#include "model.h"
#include "mesh.h"
#include "texture.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>

using namespace std;

Model::Model(const std::string& file_path)
{
    loadModel(file_path);
}

void Model::loadModel(const std::string& file_path)
{
    Assimp::Importer importer;
    auto scene = importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);
    if(scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr) {
        throw runtime_error("Could not load model");
    }
    loadNode(scene->mRootNode, scene);
    filesystem::path path(file_path);
    m_directory = path.parent_path();
    loadMaterial(scene);
}

void Model::loadNode(aiNode* node, const aiScene* scene)
{
    for(int i=0; i<node->mNumMeshes; i++) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        loadMesh(mesh, scene);
    }
    for(int i=0; i<node->mNumChildren; i++) {
        loadNode(node->mChildren[i], scene);
    }
}

void Model::loadMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<GLfloat> vertices;
    vector<unsigned int> indices;
    for(int i=0; i<mesh->mNumVertices; i++) {
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);
        if(mesh->mTextureCoords[0]) {
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        } else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);
    }
    for(int i=0; i<mesh->mNumFaces; i++) {
        auto face = mesh->mFaces[i];
        for(int j=0; j<face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    auto new_mesh = new Mesh();
    new_mesh->createMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
    m_meshes.push_back(new_mesh);
    m_mesh_to_texture.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterial(const aiScene* scene)
{
    m_textures.resize(scene->mNumMaterials);
    for(int i=0; i<scene->mNumMaterials; i++) {
        auto material = scene->mMaterials[i];
        m_textures[i] = nullptr;
        if(material->GetTextureCount(aiTextureType_DIFFUSE)) {
            aiString path;
            if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
                filesystem::path file_path(string(path.data));
                filesystem::path total_path("Textures");
                total_path /= file_path.filename();
                m_textures[i] = new Texture(total_path);
                if(!m_textures[i]->loadTextureRGB()) {
                    delete m_textures[i];
                    m_textures[i] = nullptr;
                }
            }
        }
        if(m_textures[i] == nullptr) {
            m_textures[i] = new Texture("Textures/plain.png");
            m_textures[i]->loadTexture();
        }
    }
}

void Model::clearModel()
{
    for(int i=0; i<m_meshes.size(); i++) {
        delete m_meshes[i];
    }
    for(int i=0; i<m_textures.size(); i++) {
        delete m_textures[i];
    }
    m_meshes.clear();
    m_textures.clear();
    m_mesh_to_texture.clear();
}

Model::~Model()
{
    clearModel();
}

void Model::renderModel()
{
    for(int i=0; i<m_meshes.size(); i++) {
        auto texture_index = m_mesh_to_texture[i];
        if(texture_index < m_textures.size() && m_textures[texture_index] != nullptr) {
            m_textures[texture_index]->useTexture();
        }
        m_meshes[i]->renderMesh();
    }
}