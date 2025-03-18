#ifndef RENDERERGL_HPP
#define RENDERERGL_HPP

#include "../common/Renderer.hpp"
#include "shader/Shader.hpp"
#include "internal/camera/Camera.hpp"
#include "internal/RendererStructs.hpp"
#include "core/config/ConfigManager.hpp"
#include "stb_image.h"
#include <glfw/glfw3.h>


class RendererGL : public Renderer
{
    u32 SCREEN_WIDTH, SCREEN_HEIGHT;
    ConfigManager* m_configManager;
public:
    RendererGL(ConfigManager& configManager)
    : m_configManager(&configManager){}
    bool init() override;
    bool deinit() override;
    void render() override;
    ~RendererGL();
protected:
};

#endif