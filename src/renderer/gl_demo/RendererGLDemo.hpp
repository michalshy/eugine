#ifndef RENDERERGLDEMO_HPP
#define RENDERERGLDEMO_HPP

#include "../common/Renderer.hpp"
#include "../gl_renderer/shader/Shader.hpp"
#include "../gl_renderer/internal/camera/Camera.hpp"
#include "../gl_renderer/internal/RendererStructs.hpp"
#include "core/config/ConfigManager.hpp"
#include "stb_image.h"
#include <glfw/glfw3.h>

class RendererGLDemo : public Renderer
{
    u32 SCREEN_WIDTH, SCREEN_HEIGHT;
    ConfigManager* m_configManager;
    GLFWwindow* m_window;
    float deltaTime, lastFrame;
    Shader objSh = Shader("./res/default/shaders/sh.vert", "./res/default/shaders/sh.frag");
    Shader lghtSh = Shader("./res/default/shaders/shL.vert", "./res/default/shaders/shL.frag");
public:
    RendererGLDemo(ConfigManager& configManager, GLFWwindow* window)
    : m_configManager(&configManager), m_window(window) {}
    bool init() override;
    bool deinit() override;
    void render() override;
    ~RendererGLDemo();
protected:
    static Camera m_viewport_camera;
    u32 loadTexture(char const* path);
    void initDefault();
    void renderDefault();
    bool m_demo;
    GLDemoStruct m_demoStruct;
    void processInput(GLFWwindow* window);
    static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static float lastX, lastY;
};

#endif