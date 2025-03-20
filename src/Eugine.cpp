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

    return true;
}

void Eugine::loop()
{
    m_renderManager.render();
    shutDown();
}

void Eugine::shutDown()
{
    m_renderManager.shutDown();
    m_configManager.shutDown();
}


