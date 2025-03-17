#ifndef IDK_HPP
#define IDK_HPP

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

    ~Eugine();
};

#endif