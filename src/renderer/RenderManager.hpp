#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "common/Renderer.hpp"
#include "gl_renderer/RendererGL.hpp"
#include "directx_renderer/RendererDX.hpp"
#include "../core/memory/StackAllocator.hpp"
#include "../common/Manager.hpp"
#include "../core/config/Config.hpp"
#include <GLFW/glfw3.h>

constexpr char* kDefaultRenderType = "directx";

class RenderManager : public Manager
{
    StackAllocator m_allocator;
    GLFWwindow* m_window;
    Renderer* m_renderer;
public:
    RenderManager();
    bool startUp() override;
    bool shutDown() override;
    void render();

    ~RenderManager();
protected:
    bool setRenderer();
private:
    static void processInput(GLFWwindow* window);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif