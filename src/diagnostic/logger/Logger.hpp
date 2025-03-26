#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>

class Logger
{
public:
    Logger();
    ~Logger();
    static void Log(const char* message)
    {
        std::cout << message << std::endl;
    }
};

#endif