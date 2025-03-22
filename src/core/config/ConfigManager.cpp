#include "ConfigManager.hpp"
#include <fstream>

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
    for(it = m_engineOptions.begin(); it != m_engineOptions.end(); ++it)
    {
        if(it->section == section)
        {
            if(it->key == key)
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
                    //process key value pair
                    m_engineOptions.emplace_back(lastSection, line.substr(0, idx), line.substr(idx + 1, line.size() - 1));
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
