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

    //TODO: provide rendered from configuration
    void* addr = m_allocator.alloc(sizeof(RendererGL));
    if(addr != nullptr)
    {
        m_renderer = new (addr) RendererGL();
        if(!m_renderer->startUp())
        {
            return false;
        }
    }
    else
    {

        return false;
    }

    return true;
}

bool RenderManager::shutDown()
{
    delete m_renderer;
    return true;
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

void RenderManager::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void RenderManager::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
