#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "common/Renderer.hpp"
#include "../core/config/ConfigManager.hpp"
#include "common/RendererStructs.hpp"
#include "core/alloc/StackAllocator.hpp"
#include <GLFW/glfw3.h>
#include "FrameBuffer.hpp"
#include "utils/Subsystem.hpp"

class RenderManager : public Subsystem
{
    //variables
    u32 screenWidth, screenHeight;
    RenderType renderType;
    //memory
    StackAllocator allocator;
    //pointers
    GLFWwindow* window;
    Renderer* renderer;
    ConfigManager* configManager;
public:
    RenderManager(ConfigManager& _configManager) : configManager(&_configManager) { /* Do nothing! */ };
    bool StartUp() override;
    bool ShutDown() override;

    void Render();

    FrameBuffer* GetFrameBuffer();
    bool WindowState();
    RenderType GetRenderType();
    GLFWwindow* GetWindow();

    ~RenderManager();
protected:
    bool LowLevelInit();
    bool ChooseRenderer();
};

#endif