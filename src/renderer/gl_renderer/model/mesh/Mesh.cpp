#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<u32> _indices, std::vector<Texture> _textures)
{
    vertices = _vertices;
    indices = _indices;
    textures = _textures;
    SetupMesh();
}

Mesh::~Mesh(){ /* Do nothing */ }

void Mesh::Draw(Shader& shader)
{
    u32 diffuseNr = 1;
    u32 specularNr = 1;
    for(u32 i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string number;
        std::string type = textures[i].type == TexType::DIFFUSE ? "texture_diffuse" : "texture_specular";
        if(type == "texture_diffuse")
        {
            number = std::to_string(diffuseNr++);
        }
        else if(type == "texture_specular")
        {
            number = std::to_string(specularNr++);
        }
        shader.SetInt((type+number).c_str(), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    //set to default
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::SetupMesh()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(u32), &indices[0], GL_STATIC_DRAW);
    //vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, normal));
    //vertex texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));
}