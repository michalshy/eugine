#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "common/Renderer.hpp"
#include "gl_renderer/RendererGL.hpp"
#include "../core/memory/StackAllocator.hpp"
#include <GLFW/glfw3.h>

class RenderManager
{
    StackAllocator m_allocator;
    GLFWwindow* m_window;
    Renderer* m_renderer;
public:
    RenderManager();
    bool startUp();
    bool shutDown();
    void render();

    ~RenderManager();
protected:
    static void processInput(GLFWwindow* window);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif