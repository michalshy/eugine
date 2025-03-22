#include "RenderManager.hpp"
#include "GLFW/glfw3.h"
#include "FrameBuffer.hpp"
#include "gl_demo/RendererGLDemo.hpp"
#include "gl_renderer/RendererGL.hpp"
#include "directx_renderer/RendererDX.hpp"
#include "renderer/common/RendererStructs.hpp"

RenderManager::RenderManager()
{
    //Do nothing
}

RenderManager::~RenderManager()
{
    //Do nothing
}

bool RenderManager::startUp(ConfigManager& configManager)
{
    m_configManager = &configManager;
    //initialize glad, opengl, glfw
    if(!lowLevelInit()) return false;
    //check for renderer
    if(!chooseRenderer()) return false;
    //initialize renderer
    if(!m_renderer->init()) return false;
    return true;
}

bool RenderManager::shutDown()
{
    
    // Cleanup glfw
    glfwDestroyWindow(m_window);
    glfwTerminate();
    //Clear stack allocator
    m_allocator.clear();
    return true;
}

void RenderManager::render()
{
    m_renderer->render();
}

FrameBuffer* RenderManager::getFrameBuffer()
{
    return m_renderer->getFrameBuffer();
}

bool RenderManager::windowState()
{
    return !glfwWindowShouldClose(m_window);
}

RenderType RenderManager::getRenderType()
{
    return m_rType;
}

GLFWwindow* RenderManager::getWindow()
{
    return m_window;
}

bool RenderManager::lowLevelInit()
{
    m_screenHeight = std::stoi(m_configManager->getEngineOption("renderer", "screen_height"));
    m_screenWidth = std::stoi(m_configManager->getEngineOption("renderer", "screen_width"));
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Create window
    m_window = glfwCreateWindow(800, 600, "EUGINE", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync
    // Setup GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return false;
    }
    
    glViewport(0, 0, m_screenWidth, m_screenHeight);

    return true;
}

bool RenderManager::chooseRenderer()
{
    //Define type
    std::string type = m_configManager->getEngineOption("renderer", "type");
    if(type == "opengl")
        m_rType = RenderType::OPENGL;
    else if(type == "directx")
        m_rType = RenderType::DIRECTX;
    else 
        m_rType = RenderType::OPENGL;

    //check if demo or real renderer is loaded
    std::string isDemo = m_configManager->getEngineOption("renderer", "demo");
    
    if(m_rType == RenderType::OPENGL)
    {
        //check if demo should be played
        if(isDemo == "y")
        {
            //allocate memory for demo renderer
            void* addr = m_allocator.alloc(sizeof(RendererGLDemo));
            if(addr != nullptr) //if success
            {
                //allocate new object at address
                //IMPORTANT: THIS IS NOT SYSCALL
                m_renderer = new (addr) RendererGLDemo(*m_configManager, m_window);
            }
            else 
            {
                return false;
            }
        }
        else
        {
            //allocate memory for standard OpenGL renderer
            void* addr = m_allocator.alloc(sizeof(RendererGL));
            if(addr != nullptr)
                //allocate new object at address
                //IMPORTANT: THIS IS NOT SYSCALL
                m_renderer = new (addr) RendererGL(*m_configManager);
            else
                return false;
        }
    }
    else if(m_rType == RenderType::DIRECTX) //check for direct, other instructions are the same
    {
        void* addr = m_allocator.alloc(sizeof(RendererDX));
        if(addr != nullptr)
            m_renderer = new (addr) RendererDX();
        else
            return false;
    }
    else
    {
        return false;
    }

    return true;
}
