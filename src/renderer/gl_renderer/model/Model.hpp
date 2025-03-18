#ifndef MODEL_HPP
#define MODEL_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "stb_image.h"

#include <vector>
#include "mesh/Mesh.hpp"

class Model
{
public:
    Model(std::string const& path);
    void draw(Shader& shader);
    ~Model();
private:
    std::vector<Mesh> meshes;
    std::string directory;
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTexture(aiMaterial* mat, aiTextureType type, TexType typeName);
    u32 textureFromFile(const char* path, const std::string& directory);
};

#endif