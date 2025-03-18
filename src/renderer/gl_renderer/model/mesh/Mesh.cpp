#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<u32> indices, std::vector<Texture> textures)
{
    m_vertices = vertices;
    m_indices = indices;
    m_textures = textures;
}

void Mesh::draw(Shader& shader)
{
    u32 diffuseNr = 1;
    u32 specularNr = 1;
    for(u32 i = 0; i < m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string type = m_textures[i].type == TexType::DIFFUSE ? "texture_diffuse" : "texture_specular";
        if(type == "texture_diffuse")
        {
            number = std::to_string(diffuseNr++);
        }
        else if(type == "texture_specular")
        {
            number = std::to_string(specularNr++);
        }
        shader.setInt(("material."+type+number).c_str(), i);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    //Do nothing
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(u32), &m_indices[0], GL_STATIC_DRAW);
    //vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
    //vertex texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));
}