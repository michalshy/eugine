#ifndef RENDERERSTRUCTS_HPP
#define RENDERERSTRUCTS_HPP

#include "TypeDef.hpp"
#include <string>
#include <glm/glm.hpp>

enum class RenderType
{
    OPENGL,
    DIRECTX
};

enum TexType {
    DIFFUSE,
    SPECULAR
};

struct Texture {
    u32 id;
    TexType type;
    std::string path;
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct GLDemoStruct {
    u32 objectVAO; 
    u32 VBO;
    u32 lightVAO;
    u32 tDiffuse; 
    u32 tSpecular;
};

#endif