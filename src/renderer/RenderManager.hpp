#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "common/Renderer.hpp"
#include "core/config/ConfigManager.hpp"
#include "gl_renderer/RendererGL.hpp"
#include "directx_renderer/RendererDX.hpp"
#include "core/memory/StackAllocator.hpp"
#include "utils/Manager.hpp"
#include <GLFW/glfw3.h>

static const char* kDefaultRenderType = "directx";

class RenderManager : public Manager
{
    StackAllocator m_allocator;
    GLFWwindow* m_window;
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
    static void processInput(GLFWwindow* window);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif