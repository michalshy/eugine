#ifndef RENDERERDX_HPP
#define RENDERERDX_HPP

#include "../common/Renderer.hpp"

class RendererDX : public Renderer
{
public:
    RendererDX();
    bool Init() override;
    bool Deinit() override;
    void Render() override;
    FrameBuffer* GetFrameBuffer() override;
    ~RendererDX();
private:

};

#endif