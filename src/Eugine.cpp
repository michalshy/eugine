#include "Eugine.hpp"

Eugine::Eugine()
{
    //Do nothing
}

Eugine::~Eugine()
{
    //Do nothing
}

bool Eugine::boot()
{
    if(!m_configManager.startUp()) return false;
    
    if(!m_renderManager.startUp(m_configManager)) return false;

    if(!m_guiManager.startUp(m_configManager, m_renderManager)) return false;

    if(!m_editorManager.startUp(m_configManager, m_guiManager)) return false;

    return true;
}

void Eugine::engine()
{
    while(m_renderManager.windowState())
    {
        m_renderManager.render();
        m_editorManager.contructEditor();
    }
    shutDown();
}

void Eugine::shutDown()
{
    m_editorManager.shutDown();
    m_guiManager.shutDown();
    m_renderManager.shutDown();
    m_configManager.shutDown();
}


