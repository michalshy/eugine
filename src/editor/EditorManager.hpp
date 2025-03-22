#ifndef EDITOR_HPP
#define EDITOR_HPP

#include "core/config/ConfigManager.hpp"
#include "gui/GUIManager.hpp"

struct EditorStates
{
    bool globalWindowState = true;
    bool menuBarState = true;
    bool viewPortState = true;
    bool sceneHierarchyState = true;
    bool inspectorState = true;
    bool assetBrowserState = true;
};

class EditorManager
{
    ConfigManager* m_configManager;
    GUIManager* m_guiManager;
    EditorStates m_editorStates;
public:
    EditorManager();
    ~EditorManager();
    bool startUp(ConfigManager configManager, GUIManager& guiManager);
    bool shutDown();
    void contructEditor();
private:
    void constructGlobalWindow();
    void constructMenuBar();
    void constructViewport();
    void constructSceneHierarchy();
    void constructInspector();
    void constructAssetBrowser();
};

#endif