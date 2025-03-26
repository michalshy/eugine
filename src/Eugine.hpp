#ifndef IDK_HPP
#define IDK_HPP

#define GL_SILENCE_DEPRECATION
#include "renderer/RenderManager.hpp"
#include "config/ConfigManager.hpp"
#include "gui/GUIManager.hpp"
#include "editor/EditorManager.hpp"

class Eugine
{
    EditorManager editorManager;
    RenderManager renderManager;
    GUIManager guiManager;
    ConfigManager configManager;
public:
    Eugine() : 
    renderManager(configManager), 
    guiManager(configManager, renderManager), 
    editorManager(configManager, guiManager)
    { /*Do nothing*/ };

    bool Boot();
    void Engine();
    void ShutDown();

    ~Eugine();
};

#endif