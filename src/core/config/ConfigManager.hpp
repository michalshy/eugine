#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include <list>
#include <string>

struct Option {
    Option(std::string _section, std::string _key, std::string _value) :
        section(_section), key(_key), value(_value) {}
    std::string section;
    std::string key;
    std::string value;
};

class ConfigManager
{
    std::list<Option> m_engineOptions;
public:
    ConfigManager();
    bool startUp();
    bool shutDown();

    void parseConfig();
    std::string getEngineOption(std::string section, std::string key);
    ~ConfigManager();
protected:
    void parseEngineConfig();
    void parseResourceConfig();
    void parseAddonsConfig();
};

#endif