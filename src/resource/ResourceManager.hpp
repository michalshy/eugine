#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "utils/Manager.hpp"

class ResourceManager : public Manager
{
public:
    // Constructor / Destructor
    ResourceManager();
    ~ResourceManager();
    // Interface
    bool startUp() override;
    bool shutDown() override;
private:

};

#endif