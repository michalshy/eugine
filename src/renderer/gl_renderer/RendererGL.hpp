#ifndef RENDERERGL_HPP
#define RENDERERGL_HPP

#include "../common/Renderer.hpp"
#include "shader/Shader.hpp"
#include "camera/Camera.hpp"

class RendererGL : public Renderer
{
public:
    RendererGL();
    bool init() override;
    bool deinit() override;
    void render() override;
    ~RendererGL();
private:
};

#endif