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
    
    m_renderManager.setConfig(m_configManager);
    if(!m_renderManager.startUp()) return false;

    if(!m_guiManager.startUp()) return false;

    return true;
}

void Eugine::engine()
{
    m_renderManager.render();
    shutDown();
}

void Eugine::shutDown()
{
    m_guiManager.shutDown();
    m_renderManager.shutDown();
    m_configManager.shutDown();

}


