#include "SceneManager.hpp"

SceneManager::SceneManager(){ /* Do nothing */ }
SceneManager::~SceneManager(){ /* Do nothing */ }

bool SceneManager::StartUp()
{
    bool returnValue = true;
    if(!BuildDefaultScene())
    {
        returnValue = false;
    }
    return returnValue;
}

bool SceneManager::ShutDown()
{
    return true;
}

bool SceneManager::BuildDefaultScene()
{
    return true;
}