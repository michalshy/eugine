#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "renderer/FrameBuffer.hpp"

/**
 * @brief Interface for rendering of choice
 */

class Renderer
{
public:
    Renderer() = default;
    virtual bool init() = 0;
    virtual bool deinit() = 0; 
    virtual void render() = 0;
    virtual FrameBuffer* getFrameBuffer() = 0;
    virtual ~Renderer(){};
};

#endif // RENDERER_HPP