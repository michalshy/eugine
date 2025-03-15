#ifndef RENDERER_HPP
#define RENDERER_HPP

/**
 * @brief Interface for rendering of choice
 */

class Renderer
{
public:
    virtual bool init() = 0;
    virtual bool deinit() = 0; 
    virtual void render() = 0;
};

#endif // RENDERER_HPP