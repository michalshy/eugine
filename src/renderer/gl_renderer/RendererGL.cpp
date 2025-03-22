#include "RendererGL.hpp"

bool RendererGL::init()
{
    SCREEN_WIDTH = std::stoi(m_configManager->getEngineOption("renderer", "screen_width"));
    SCREEN_HEIGHT = std::stoi(m_configManager->getEngineOption("renderer", "screen_height"));

    return true;
}

bool RendererGL::deinit()
{
    return true;
}

void RendererGL::render()
{
}

FrameBuffer* RendererGL::getFrameBuffer()
{
    return nullptr;
}

RendererGL::~RendererGL()
{
}
