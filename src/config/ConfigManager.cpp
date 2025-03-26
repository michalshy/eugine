#include "ConfigManager.hpp"
#include <fstream>

ConfigManager::ConfigManager()
{
    //Do nothing
}

bool ConfigManager::StartUp()
{
    ParseConfig();
    return true;
}

void ConfigManager::ParseConfig()
{
    ParseEngineConfig();
    ParseResourceConfig();
    ParseAddonsConfig();
}

std::string ConfigManager::GetEngineOption(std::string section, std::string key)
{
    std::list<Option>::iterator it;
    for(it = engineOptions.begin(); it != engineOptions.end(); ++it)
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

bool ConfigManager::ShutDown()
{
    return true;
}

ConfigManager::~ConfigManager()
{
    //Do nothing
}

void ConfigManager::ParseEngineConfig()
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
                    engineOptions.emplace_back(lastSection, line.substr(0, idx), line.substr(idx + 1, line.size() - 1));
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

void ConfigManager::ParseResourceConfig()
{
}

void ConfigManager::ParseAddonsConfig()
{
}
