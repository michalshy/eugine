#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "common/Renderer.hpp"
#include "../core/config/ConfigManager.hpp"
#include "common/RendererStructs.hpp"
#include "core/alloc/StackAllocator.hpp"
#include <GLFW/glfw3.h>
#include "FrameBuffer.hpp"

class RenderManager
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
public:
    RenderManager();
    bool startUp(ConfigManager& configManager);
    bool shutDown();

    void render();

    FrameBuffer* getFrameBuffer();
    bool windowState();
    RenderType getRenderType();
    GLFWwindow* getWindow();

    ~RenderManager();
protected:
    bool lowLevelInit();
    bool chooseRenderer();
};

#endif