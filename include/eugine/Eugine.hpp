#ifndef IDK_HPP
#define IDK_HPP

#include "shader/Shader.hpp"
#include "camera/Camera.hpp"
#include <GLFW/glfw3.h>

class Eugine
{
    GLFWwindow* window;
public:
    Eugine();

    bool init();
    void run();

    ~Eugine();

protected:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);
private:
    //TODO: Add private members here
};

#endif