#include "Eugine.hpp"
#include "core/alloc/PoolAllocator.hpp"

Eugine::~Eugine()
{
    //Do nothing
}

bool Eugine::Boot()
{
    PoolAllocator<u32> pool(13);
    if(!configManager.StartUp()) return false;
    
    if(!renderManager.StartUp()) return false;

    if(!guiManager.StartUp()) return false;

    if(!editorManager.StartUp()) return false;

    return true;
}

void Eugine::Engine()
{
    while(renderManager.WindowState())
    {
        renderManager.Render();
        editorManager.ContructEditor();
    }
    ShutDown();
}

void Eugine::ShutDown()
{
    editorManager.ShutDown();
    guiManager.ShutDown();
    renderManager.ShutDown();
    configManager.ShutDown();
}


