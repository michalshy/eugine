#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include "renderer/RenderManager.hpp"
#include "config/ConfigManager.hpp"
#include "utils/Subsystem.hpp"

class GUIManager : public Subsystem
{
    GLFWwindow* window;
    ConfigManager* configManager;
    RenderManager* renderManager;
    bool firstTime = true;
public:
    // Constructor / Destructor
    GUIManager(ConfigManager& _configManager, RenderManager& _renderManager) :
        configManager(&_configManager),
        renderManager(&_renderManager)
    { /* Do nothing */ }
    ~GUIManager();
    // Interface
    bool StartUp() override;
    bool ShutDown() override;

    void PreGUI();
    void PostGUI();

    void ShowGlobalWindow(bool);
    void ShowMenuBar(bool);
    void ShowViewport(bool);
    void ShowSceneHierarchy(bool);
    void ShowInspector(bool);
    void ShowAssetBrowser(bool);
protected:
    bool ImguiInit();
};

#endif