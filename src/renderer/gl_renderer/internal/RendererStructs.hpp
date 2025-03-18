#ifndef RENDERERSTRUCTS_HPP
#define RENDERERSTRUCTS_HPP

#include "TypeDef.hpp"
#include "../shader/Shader.hpp"

struct GLDemoStruct {
    u32 objectVAO; 
    u32 VBO;
    u32 lightVAO;
    u32 tDiffuse; 
    u32 tSpecular;
};

#endif