#include "RenderManager.hpp"

RenderManager::RenderManager()
{
    //Do nothing
}

RenderManager::~RenderManager()
{
    //Do nothing
}



bool RenderManager::startUp()
{
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

    // Setup GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    
    if(!setRenderer())
    {
        return false;
    }

    return true;
}

bool RenderManager::shutDown()
{
    m_allocator.clear();
    return true;
}

void RenderManager::setConfig(ConfigManager& configManager)
{
    m_configManager = &configManager;
}

void RenderManager::render()
{
    while(!glfwWindowShouldClose(m_window))
    {
        processInput(m_window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        m_renderer->render();
    
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

bool RenderManager::setRenderer()
{
    //TODO: provide rendered from configuration
    void* addr = m_allocator.alloc(sizeof(RendererGL));
    if(addr != nullptr)
    {
        std::string type = m_configManager->getEngineOption("renderer", "type");
        std::string isDemo = m_configManager->getEngineOption("renderer", "demo");
        if(type == "opengl")
        {
            if(isDemo == "y")
                m_renderer = new (addr) RendererGLDemo(*m_configManager, m_window);
            else
                m_renderer = new (addr) RendererGL(*m_configManager);
        }
        else if(type == "directx")
        {
            m_renderer = new (addr) RendererDX();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    if(!m_renderer->init())
    {
        return false;
    }

    return true;
}

void RenderManager::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void RenderManager::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

