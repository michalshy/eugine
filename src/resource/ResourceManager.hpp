#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "utils/Subsystem.hpp"

class ResourceManager : public Subsystem
{
public:
    // Constructor / Destructor
    ResourceManager();
    ~ResourceManager();
    // Interface
    bool StartUp() override;
    bool ShutDown() override;
private:

};

#endif