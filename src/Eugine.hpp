#ifndef IDK_HPP
#define IDK_HPP

#define GL_SILENCE_DEPRECATION
#include "renderer/RenderManager.hpp"
#include "core/config/ConfigManager.hpp"
#include "gui/GUIManager.hpp"

class Eugine
{
    RenderManager m_renderManager;
    GUIManager m_guiManager;
    ConfigManager m_configManager;
public:
    Eugine();

    bool boot();
    void engine();
    void shutDown();

    ~Eugine();
};

#endif