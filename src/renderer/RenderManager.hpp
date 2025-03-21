#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "common/Renderer.hpp"
#include "../core/config/ConfigManager.hpp"
#include "gl_demo/RendererGLDemo.hpp"
#include "gl_renderer/RendererGL.hpp"
#include "directx_renderer/RendererDX.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "core/alloc/StackAllocator.hpp"
#include "utils/Manager.hpp"
#include <GLFW/glfw3.h>
#include "../gui/GUIManager.hpp"

static const char* kDefaultRenderType = "directx";

class RenderManager : public Manager
{
    //variables
    u32 m_screenWidth, m_screenHeight;
    RenderType m_rType;
    //memory
    StackAllocator m_allocator;
    //pointers
    GLFWwindow* m_window;
    Renderer* m_renderer;
    ConfigManager* m_configManager;
    GUIManager* m_guiManager;
public:
    RenderManager();
    bool startUp() override;
    bool shutDown() override;

    void setConfig(ConfigManager& configManager);
    void render();

    ~RenderManager();
protected:
    bool lowLevelInit();
    bool imguiInit();
    bool chooseRenderer();
};

#endif