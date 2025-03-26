#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "utils/Subsystem.hpp"
#include "prot/Scene.hpp"

#include <vector>

class SceneManager : Subsystem
{
    std::vector<Scene> scenes;
public:
    SceneManager();
    ~SceneManager();
    bool StartUp() override;
    bool ShutDown() override;
private:
    bool BuildDefaultScene();
};

#endif