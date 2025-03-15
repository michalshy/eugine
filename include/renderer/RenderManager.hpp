#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP

#include "renderer/shader/Shader.hpp"
#include "renderer/camera/Camera.hpp"
#include <GLFW/glfw3.h>

class RenderManager
{
    GLFWwindow* window;
public:
    explicit RenderManager() = default;
    ~RenderManager() = default;
    bool startUp();
    bool shutDown();
    void render();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);
};

#endif