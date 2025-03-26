#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "config/ConfigManager.hpp"
#include "gui/GUIManager.hpp"
#include "utils/Subsystem.hpp"
struct EditorStates
{
    bool globalWindowState = true;
    bool menuBarState = true;
    bool viewPortState = true;
    bool sceneHierarchyState = true;
    bool inspectorState = true;
    bool assetBrowserState = true;
};

class EditorManager : public Subsystem
{
    ConfigManager* configManager;
    GUIManager* guiManager;
    EditorStates editorStates;
public:
    EditorManager(ConfigManager& _configManager, GUIManager& _guiManager) :
        configManager(&_configManager),
        guiManager(&_guiManager)
    { /* Do nothing */ }
    ~EditorManager();
    bool StartUp() override;
    bool ShutDown() override;
    void ContructEditor();
private:
    void ConstructGlobalWindow();
    void ConstructMenuBar();
    void ConstructViewport();
    void ConstructSceneHierarchy();
    void ConstructInspector();
    void ConstructAssetBrowser();
};

#endif