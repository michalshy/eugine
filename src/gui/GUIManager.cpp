#include "GUIManager.hpp"
#include "imgui.h"

GUIManager::GUIManager() { /*Do nothing*/ } 
GUIManager::~GUIManager() { /*Do nothing*/ }

bool  GUIManager::startUp() {
    return true;
}

bool GUIManager::shutDown() {
    return true;
}

void GUIManager::createGUI() {
    ImGui::ShowDemoWindow(&state);
}