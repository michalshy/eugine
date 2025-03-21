#ifndef RENDERERGLDEMO_HPP
#define RENDERERGLDEMO_HPP

#include "../common/Renderer.hpp"
#include "../gl_renderer/model/Model.hpp"
#include "../gl_renderer/camera/Camera.hpp"
#include "../common/RendererStructs.hpp"
#include "core/config/ConfigManager.hpp"
#include "stb_image.h"

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
    bool m_demo;
    GLDemoStruct m_demoStruct;

    void processInput(GLFWwindow* window);
    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static float lastX, lastY;
};

#endif