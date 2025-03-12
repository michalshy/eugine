#ifndef IDK_HPP
#define IDK_HPP

#include "shader/Shader.hpp"
#include "camera/Camera.hpp"
#include <GLFW/glfw3.h>

class Idk
{
    GLFWwindow* window;
public:
    Idk();

    bool init();
    void run();

    ~Idk();

protected:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);
private:
    //TODO: Add private members here
};

#endif