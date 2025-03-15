#ifndef IDK_HPP
#define IDK_HPP

#include "renderer/RenderManager.hpp"

class Eugine
{
    RenderManager m_renderManager;
public:
    Eugine();

    bool boot();
    void loop();

    ~Eugine();
};

#endif