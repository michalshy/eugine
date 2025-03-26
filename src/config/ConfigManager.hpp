#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include <list>
#include <string>
#include "utils/Subsystem.hpp"

struct Option {
    Option(std::string _section, std::string _key, std::string _value) :
        section(_section), key(_key), value(_value) {}
    std::string section;
    std::string key;
    std::string value;
};

class ConfigManager : public Subsystem
{
    std::list<Option> engineOptions;
public:
    ConfigManager();
    bool StartUp();
    bool ShutDown();

    void ParseConfig();
    std::string GetEngineOption(std::string section, std::string key);
    ~ConfigManager();
protected:
    void ParseEngineConfig();
    void ParseResourceConfig();
    void ParseAddonsConfig();
};

#endif