#ifndef MESH_HPP
#define MESH_HPP

#include "../../../common/RendererStructs.hpp"
#include "../../shader/Shader.hpp"
#include "TypeDef.hpp"
#include <vector>

class Mesh
{
    std::vector<Vertex> m_vertices;
    std::vector<u32> m_indices;
    std::vector<Texture> m_textures;
public:
    Mesh(std::vector<Vertex> vertices, 
        std::vector<u32> indices, 
        std::vector<Texture> textures);
    ~Mesh();
    void draw(Shader& shader);
private:
    u32 VAO, VBO, EBO;
    void setupMesh();
};

#endif