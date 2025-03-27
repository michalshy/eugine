#include "RenderManager.hpp"
#include "GLFW/glfw3.h"
#include "FrameBuffer.hpp"
#include "gl_demo/RendererGLDemo.hpp"
#include "gl_renderer/RendererGL.hpp"
#include "directx_renderer/RendererDX.hpp"
#include "diagnostic/logger/Logger.hpp"
#include "renderer/common/RendererStructs.hpp"

RenderManager::~RenderManager()
{
    //Do nothing
}

bool RenderManager::StartUp()
{
    //check pointer
    if(configManager == nullptr) return false;
    //initialize glad, opengl, glfw
    if(!LowLevelInit()) return false;
    //check for renderer
    if(!ChooseRenderer()) return false;
    //initialize renderer
    if(!renderer->Init()) return false;
    return true;
}

bool RenderManager::ShutDown()
{
    // Cleanup glfw
    glfwDestroyWindow(window);
    glfwTerminate();
    //Clear stack allocator
    allocator.Clear();
    return true;
}

void RenderManager::Render()
{
    renderer->Render();
}

FrameBuffer* RenderManager::GetFrameBuffer()
{
    return renderer->GetFrameBuffer();
}

bool RenderManager::WindowState()
{
    return !glfwWindowShouldClose(window);
}

RenderType RenderManager::GetRenderType()
{
    return renderType;
}

GLFWwindow* RenderManager::GetWindow()
{
    return window;
}

bool RenderManager::LowLevelInit()
{
    screenHeight = std::stoi(configManager->GetEngineOption("renderer", "screen_height"));
    screenWidth = std::stoi(configManager->GetEngineOption("renderer", "screen_width"));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Create window
    window = glfwCreateWindow(800, 600, "EUGINE", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    // Setup GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return false;
    }
    
    glViewport(0, 0, screenWidth, screenHeight);

    return true;
}

bool RenderManager::ChooseRenderer()
{
    //Define type
    std::string type = configManager->GetEngineOption("renderer", "type");
    if(type == "opengl")
        renderType = RenderType::OPENGL;
    else if(type == "directx")
        renderType = RenderType::DIRECTX;
    else 
        renderType = RenderType::OPENGL;

    //check if demo or real renderer is loaded
    std::string isDemo = configManager->GetEngineOption("renderer", "demo");
    
    if(renderType == RenderType::OPENGL)
    {
        //check if demo should be played
        if(isDemo == "y")
        {
            //allocate memory for demo renderer
            try {
                void* addr = allocator.Alloc(sizeof(RendererGLDemo));
                if(addr != nullptr) //if success
                {
                    //allocate new object at address
                    //IMPORTANT: THIS IS NOT SYSCALL
                    renderer = new (addr) RendererGLDemo(*configManager, window);
                }
                else 
                {
                    return false;
                }
            } catch (std::exception& e) {
                Logger::LogError(e.what());
            }
        }
        else
        {
            //allocate memory for demo renderer
            try {
                void* addr = allocator.Alloc(sizeof(RendererGL));
                if(addr != nullptr) //if success
                {
                    //allocate new object at address
                    //IMPORTANT: THIS IS NOT SYSCALL
                    renderer = new (addr) RendererGL(*configManager);
                }
                else 
                {
                    return false;
                }
            } catch (std::exception& e) {
                Logger::LogError(e.what());
            }
        }
    }
    else if(renderType == RenderType::DIRECTX) //check for direct, other instructions are the same
    {
        //allocate memory for demo renderer
        try {
            void* addr = allocator.Alloc(sizeof(RendererDX));
            if(addr != nullptr) //if success
            {
                //allocate new object at address
                //IMPORTANT: THIS IS NOT SYSCALL
                renderer = new (addr) RendererDX();
            }
            else 
            {
                return false;
            }
        } catch (std::exception& e) {
            Logger::LogError(e.what());
        }
    }
    else
    {
        return false;
    }

    return true;
}
