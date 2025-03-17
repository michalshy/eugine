#include "ConfigManager.hpp"

ConfigManager::ConfigManager()
{
    //Do nothing
}

bool ConfigManager::startUp()
{
    parseConfig();
    return true;
}

void ConfigManager::parseConfig()
{
    parseEngineConfig();
}

std::string ConfigManager::getEngineOption(std::string section, std::string key)
{
    std::list<Option>::iterator it;
    u64 sH = computeHash(section);
    u64 kH = computeHash(key);
    for(it = m_engineOptions.begin(); it != m_engineOptions.end(); ++it)
    {
        if(it->section == sH)
        {
            if(it->key == kH)
            {
                return it->value;
            }
        }
    }
    return "";
}

bool ConfigManager::shutDown()
{
    return true;
}

ConfigManager::~ConfigManager()
{
    //Do nothing
}

void ConfigManager::parseEngineConfig()
{
    std::ifstream file("./config/eugine.cfg");
    std::string lastSection = "";
    if(file.is_open())
    {

        std::string line;
        while(std::getline(file, line))
        {
            //parse line
            //determine if it is a comment
            if(line[0] == ';' && line[1] == ';')
            {
                continue;
            }
            //determine if it is a section
            else if(line[0] == '[' && line[line.size() - 1] == ']')
            {
                //process section
                lastSection = line.substr(1, line.size() - 2);
            }
            //determine if it is a key value pair
            else
            {
                int idx = line.find('=');
                if(idx == std::string::npos)
                {
                    //log error
                    continue;
                }
                else
                {
                    //compute hashes
                    u64 secHash = computeHash(lastSection);
                    u64 keyHash = computeHash(line.substr(0, idx));
                    std::string val = line.substr(idx + 1, line.size() - 1);
                    //process key value pair
                    m_engineOptions.emplace_back(secHash, keyHash, val);
                }
            }
        }
    }
    else
    {
        //log error
    }
    file.close();
}

void ConfigManager::parseResourceConfig()
{
}

void ConfigManager::parseAddonsConfig()
{
}
