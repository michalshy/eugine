#ifndef SUBSYSTEM_HPP
#define SUBSYSTEM_HPP

/**
 * @brief Interface representing a subsystem
 * Subsytem interface is provided for unfing creation of subsystems
 * Subsystems are all the parts of the engine that can be separated
 * as a standalone module.
 */
class Subsystem
{
public:
    virtual bool StartUp() = 0;
    virtual bool ShutDown() = 0;
};

#endif