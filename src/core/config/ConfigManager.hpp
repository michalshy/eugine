#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

class ConfigManager
{
public:
    ConfigManager();
    bool startUp();
    void parseConfig();
    bool shutDown();
    ~ConfigManager();
private:

};

#endif