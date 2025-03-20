#ifndef IDK_HPP
#define IDK_HPP

#define GL_SILENCE_DEPRECATION
#include "renderer/RenderManager.hpp"
#include "core/config/ConfigManager.hpp"

class Eugine
{
    RenderManager m_renderManager;
    ConfigManager m_configManager;
public:
    Eugine();

    bool boot();
    void loop();
    void shutDown();

    ~Eugine();
};

#endif