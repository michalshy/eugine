#ifndef GUIMANAGER_HPP
#define GUIMANAGER_HPP

#include "../utils/Manager.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class GUIManager : public Manager
{
    bool state = true;
public:
    // Constructor / Destructor
    GUIManager();
    ~GUIManager();
    // Interface
    bool startUp() override;
    bool shutDown() override;
    void createGUI();
protected:

};

#endif