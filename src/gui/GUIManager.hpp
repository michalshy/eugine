#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include "renderer/RenderManager.hpp"
#include "core/config/ConfigManager.hpp"

class GUIManager
{
    GLFWwindow* m_window;
    ConfigManager* m_configManager;
    RenderManager* m_renderManager;
    bool m_firstTime = true;
public:
    // Constructor / Destructor
    GUIManager();
    ~GUIManager();
    // Interface
    bool startUp(ConfigManager& configManager, RenderManager& renderManager);
    bool shutDown();

    void preRender();
    void postRender();

    void showGlobalWindow(bool);
    void showMenuBar(bool);
    void showViewport(bool);
    void showSceneHierarchy(bool);
    void showInspector(bool);
    void showAssetBrowser(bool);
protected:
    bool imguiInit();
};

#endif