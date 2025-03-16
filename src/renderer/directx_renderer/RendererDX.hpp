#ifndef RENDERERDX_HPP
#define RENDERERDX_HPP

#include "../common/Renderer.hpp"

class RendererDX : public Renderer
{
public:
    RendererDX();
    bool init() override;
    bool deinit() override;
    void render() override;
    ~RendererDX();
private:

};

#endif