#include "EditorManager.hpp"
#include "gui/GUIManager.hpp"

EditorManager::~EditorManager(){ /* Do nothing */ }

bool EditorManager::StartUp()
{
    if(configManager == nullptr || guiManager == nullptr)
        return false;
    return true;
}

bool EditorManager::ShutDown()
{
    return true;
}

void EditorManager::ContructEditor()
{
    guiManager->PreGUI();
    
    //Create dockspace and dock windows
    ConstructGlobalWindow();
    //Create menu bar
    ConstructMenuBar();
    ConstructViewport();
    ConstructSceneHierarchy();
    ConstructInspector();
    ConstructAssetBrowser();


    guiManager->PostGUI();
}

void EditorManager::ConstructGlobalWindow()
{
    guiManager->ShowGlobalWindow(editorStates.globalWindowState);
}

void EditorManager::ConstructMenuBar()
{
    guiManager->ShowMenuBar(editorStates.menuBarState);
}

void EditorManager::ConstructViewport()
{
    guiManager->ShowViewport(editorStates.viewPortState);
}

void EditorManager::ConstructSceneHierarchy()
{
    guiManager->ShowSceneHierarchy(editorStates.sceneHierarchyState);
}

void EditorManager::ConstructInspector()
{
    guiManager->ShowInspector(editorStates.inspectorState);
}

void EditorManager::ConstructAssetBrowser()
{
    guiManager->ShowAssetBrowser(editorStates.assetBrowserState);
}