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
    
}

bool ConfigManager::shutDown()
{
    return true;
}

ConfigManager::~ConfigManager()
{
    //Do nothing
}