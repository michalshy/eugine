#ifndef RENDERERGLDEMO_HPP
#define RENDERERGLDEMO_HPP

#include "../common/Renderer.hpp"
#include "../gl_renderer/model/Model.hpp"
#include "../gl_renderer/camera/Camera.hpp"
#include "../common/RendererStructs.hpp"
#include "core/config/ConfigManager.hpp"
#include "../gl_renderer/FrameBuffer.hpp"
#include "stb_image.h"

class RendererGLDemo : public Renderer
{
    u32 m_screenWidth, m_screenHeight;
    u32 quadVAO, quadVBO;
    u32 planeVAO, planeVBO;
    unsigned int textureColorbuffer;
    unsigned int rbo;
    unsigned int framebuffer;
    u32 cubeVAO, cubeVBO;
    unsigned int cubeTexture = loadTexture("./res/default/textures/container2.png");
    unsigned int floorTexture = loadTexture("./res/default/textures/container2.png");
    ConfigManager* m_configManager;
    GLFWwindow* m_window;
    Shader shader = Shader("./res/default/shaders/shader.vs", "./res/default/shaders/shader.fs");
    float m_deltaTime, m_lastFrame;
    Shader m_objSh = Shader("./res/default/shaders/shaderModel.vs", "./res/default/shaders/shaderModel.fs");
    Shader m_screenShader = Shader("./res/default/shaders/screen.vs", "./res/default/shaders/screen.fs");
    Model m_modelDemo = Model("./res/models/backpack/backpack.obj");
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
    unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
    
};

#endif