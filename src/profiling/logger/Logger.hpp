#ifndef LOGGER_HPP
#define LOGGER_HPP

class Logger
{
public:
    Logger();
    ~Logger();
    static void log(const char* message, ...);
};

#endif