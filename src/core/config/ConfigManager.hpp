#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP

#include "../../utils/Manager.hpp"
#include <list>
#include <fstream>
#include "../hash/hash.hpp"

struct Option {
    Option(u64 _section, u64 _key, std::string _value) :
        section(_section), key(_key), value(_value) {}
    u64 section;
    u64 key;
    std::string value;
};

class ConfigManager : public Manager
{
    std::list<Option> m_engineOptions;
public:
    ConfigManager();
    bool startUp() override;
    bool shutDown() override;

    void parseConfig();
    std::string getEngineOption(std::string section, std::string key);
    ~ConfigManager();
protected:
    void parseEngineConfig();
    void parseResourceConfig();
    void parseAddonsConfig();
};

#endif