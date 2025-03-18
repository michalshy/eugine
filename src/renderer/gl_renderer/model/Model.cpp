#include "Model.hpp"

Model::Model(std::string const& path)
{
    loadModel(path);
}

void Model::draw(Shader& shader)
{
    for(u32 i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(shader);
    }
}

Model::~Model()
{

}

void Model::loadModel(std::string path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of("/"));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    for(u32 i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for(u32 i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<u32> indices;
    std::vector<Texture> textures;
    for(u32 i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        glm::vec3 normals;
        normals.x = mesh->mNormals[i].x;
        normals.y = mesh->mNormals[i].y;
        normals.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
        {
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }
    //process indices
    for(u32 i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(u32 j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    //process materials
    if(mesh->mMaterialIndex >= 0)
    {
        //process
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, TexType::DIFFUSE);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, TexType::SPECULAR);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTexture(aiMaterial *mat, aiTextureType type, TexType typeName)
{
    std::vector<Texture> textures;
    for(u32 i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        texture.id = textureFromFile(str.C_Str(), directory);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
    }
    return textures;
}

u32 Model::textureFromFile(const char* path, const std::string& directory) {
    std::string fileName = std::string(path);
    fileName = directory + '/' + fileName;
    u32 textureID;
    glGenTextures(1, &textureID);
    i32 width, height, nrComponents;
    u8* data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);
    if(data)
    {
        GLenum format;
        if(nrComponents == 1)
        {
            format = GL_RED;
        }
        else if(nrComponents == 3)
        {
            format = GL_RGB;
        }
        else if(nrComponents == 4)
        {
            format = GL_RGBA;
        }
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data); 
    }
    return textureID;
}