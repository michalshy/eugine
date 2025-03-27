#ifndef RENDERERGLDEMO_HPP
#define RENDERERGLDEMO_HPP

#include "../common/Renderer.hpp"
#include "../gl_renderer/shader/Shader.hpp"
#include "../gl_renderer/camera/Camera.hpp"
#include "../common/RendererStructs.hpp"
#include "config/ConfigManager.hpp"
#include "../FrameBuffer.hpp"
#include "stb_image.h"

class RendererGLDemo : public Renderer
{
    FrameBuffer frameBuffer;
    u32 screenWidth, screenHeight;
    ConfigManager* configManager;
    GLFWwindow* window;
    float deltaTime, lastFrame;
    Shader objectShader = Shader("./res/default/shaders/shaderModel.vs", "./res/default/shaders/shaderModel.fs");
    Shader screenShader = Shader("./res/default/shaders/screen.vs", "./res/default/shaders/screen.fs");
public:
    RendererGLDemo(ConfigManager& _configManager, GLFWwindow* _window)
    : configManager(&_configManager), window(_window)
    {}
    bool Init() override;
    bool Deinit() override;
    void Render() override;
    FrameBuffer* GetFrameBuffer() override;
    ~RendererGLDemo();
protected:
    static Camera viewportCamera;
    bool demo;
    GLDemoStruct demoStruct;

    void ProcessInput(GLFWwindow* window);
    static void MouseCallback(GLFWwindow* window, double xposIn, double yposIn);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static float lastX, lastY;
    unsigned int LoadTexture(char const * path)
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