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
    virtual bool Init() = 0;
    virtual bool Deinit() = 0; 
    virtual void Render() = 0;
    virtual FrameBuffer* GetFrameBuffer() = 0;
    virtual ~Renderer(){};
};

#endif // RENDERER_HPP