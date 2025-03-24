#ifndef MESH_HPP
#define MESH_HPP

#include "../../../common/RendererStructs.hpp"
#include "../../shader/Shader.hpp"
#include "TypeDef.hpp"
#include <vector>

class Mesh
{
    std::vector<Vertex> vertices;
    std::vector<u32> indices;
    std::vector<Texture> textures;
public:
    Mesh(std::vector<Vertex> _vertices, 
        std::vector<u32> _indices, 
        std::vector<Texture> _textures);
    ~Mesh();
    void Draw(Shader& shader);
private:
    u32 VAO, VBO, EBO;
    void SetupMesh();
};

#endif