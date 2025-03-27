#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "GLFW/glfw3.h"
#include <iostream>

class Logger
{
public:
    Logger();
    ~Logger();
    static void LogDebug(const char* message) {
        std::cout << "[DEBUG] " << message << std::endl;
    }
    static void LogInfo(const char* message) {
        std::cout << "[INFO] " << message << std::endl;
    }
    static void LogWarning(const char* message) {
        std::cout << "[WARNING] " << message << std::endl;
    }
    static void LogError(const char* message) {
        std::cerr << "[ERROR] " << message << std::endl;
        glfwTerminate(); // Terminate GLFW if an error occurs
    }
};

#endif