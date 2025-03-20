#ifndef RENDERERGLDEMO_HPP
#define RENDERERGLDEMO_HPP

#include "../common/Renderer.hpp"
#include "../gl_renderer/shader/Shader.hpp"
#include "../gl_renderer/internal/camera/Camera.hpp"
#include "../gl_renderer/internal/RendererStructs.hpp"
#include "core/config/ConfigManager.hpp"
#include "stb_image.h"
#include <glfw/glfw3.h>
#include "../gl_renderer/model/Model.hpp"

class RendererGLDemo : public Renderer
{
    u32 SCREEN_WIDTH, SCREEN_HEIGHT;
    ConfigManager* m_configManager;
    GLFWwindow* m_window;
    float deltaTime, lastFrame;
    Shader objSh = Shader("./res/default/shaders/shaderModel.vs", "./res/default/shaders/shaderModel.fs");
    Model modelDemo = Model("./res/models/backpack/backpack.obj");
public:
    RendererGLDemo(ConfigManager& configManager, GLFWwindow* window)
    : m_configManager(&configManager), m_window(window)
    {}
    bool init() override;
    bool deinit() override;
    void render() override;
    ~RendererGLDemo();
protected:
    static Camera m_viewport_camera;
    u32 loadTexture(char const* path);
    bool m_demo;
    GLDemoStruct m_demoStruct;
    void processInput(GLFWwindow* window);
    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static float lastX, lastY;
};

#endif