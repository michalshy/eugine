#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include "../../common/Manager.hpp"
#include "Config.hpp"

class ConfigManager : public Manager
{
public:
    ConfigManager();
    bool startUp() override;
    bool shutDown() override;
    void parseConfig();
    ~ConfigManager();
private:

};

#endif