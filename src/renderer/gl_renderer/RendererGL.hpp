#ifndef RENDERERGL_HPP
#define RENDERERGL_HPP

#include "../common/Renderer.hpp"
#include "config/ConfigManager.hpp"
#include "stb_image.h"
#include <glfw/glfw3.h>


class RendererGL : public Renderer
{
    ConfigManager* configManager;
public:
    RendererGL(ConfigManager& _configManager)
    : configManager(&_configManager){}
    bool Init() override;
    bool Deinit() override;
    void Render() override;
    FrameBuffer* GetFrameBuffer() override;
    ~RendererGL();
protected:
};

#endif