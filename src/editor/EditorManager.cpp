#include "EditorManager.hpp"
#include "core/config/ConfigManager.hpp"
#include "gui/GUIManager.hpp"

EditorManager::EditorManager(){ /* Do nothing */ }
EditorManager::~EditorManager(){ /* Do nothing */ }

bool EditorManager::startUp(ConfigManager configManager, GUIManager& guiManager)
{
    m_configManager = &configManager;
    m_guiManager = &guiManager;
    if(m_configManager == nullptr || m_guiManager == nullptr)
        return false;
    return true;
}

bool EditorManager::shutDown()
{
    return true;
}

void EditorManager::contructEditor()
{
    m_guiManager->preRender();
    
    //Create dockspace and dock windows
    constructGlobalWindow();
    //Create menu bar
    constructMenuBar();
    constructViewport();
    constructSceneHierarchy();
    constructInspector();
    constructAssetBrowser();


    m_guiManager->postRender();
}

void EditorManager::constructGlobalWindow()
{
    m_guiManager->showGlobalWindow(m_editorStates.globalWindowState);
}

void EditorManager::constructMenuBar()
{
    m_guiManager->showMenuBar(m_editorStates.menuBarState);
}

void EditorManager::constructViewport()
{
    m_guiManager->showViewport(m_editorStates.viewPortState);
}

void EditorManager::constructSceneHierarchy()
{
    m_guiManager->showSceneHierarchy(m_editorStates.sceneHierarchyState);
}

void EditorManager::constructInspector()
{
    m_guiManager->showInspector(m_editorStates.inspectorState);
}

void EditorManager::constructAssetBrowser()
{
    m_guiManager->showAssetBrowser(m_editorStates.assetBrowserState);
}