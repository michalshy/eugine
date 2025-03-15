#ifndef RENDERER_HPP
#define RENDERER_HPP

/**
 * @brief Interface for rendering of choice
 */

class Renderer
{
public:
    virtual bool startUp() = 0;
    virtual bool shutDown() = 0; 
    virtual void render() = 0;
};

#endif // RENDERER_HPP