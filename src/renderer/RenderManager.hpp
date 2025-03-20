#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "common/Renderer.hpp"
#include "../core/config/ConfigManager.hpp"
#include "gl_renderer/RendererGL.hpp"
#include "gl_demo/RendererGLDemo.hpp"
#include "directx_renderer/RendererDX.hpp"
#include "core/memory/StackAllocator.hpp"
#include "utils/Manager.hpp"
#include <glfw/glfw3.h>

static const char* kDefaultRenderType = "directx";

enum RenderType {
    OPENGL,
    DIRECTX,
};

class RenderManager : public Manager
{
    u32 m_screenWidth, m_screenHeight;
    StackAllocator m_allocator;
    GLFWwindow* m_window;
    RenderType m_rType;
    Renderer* m_renderer;

    ConfigManager* m_configManager;
public:
    RenderManager();
    bool startUp() override;
    bool shutDown() override;

    void setConfig(ConfigManager& configManager);
    void render();

    ~RenderManager();
protected:
    bool setRenderer();
    bool initImgui();
};

#endif