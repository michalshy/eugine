#include "GUIManager.hpp"
#include "imgui.h"
#include "imgui_internal.h"
#include "renderer/RenderManager.hpp"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
GUIManager::GUIManager() { /*Do nothing*/ } 
GUIManager::~GUIManager() { /*Do nothing*/ }

bool  GUIManager::startUp(ConfigManager& configManager, RenderManager& renderManager) {
    m_configManager = &configManager;
    m_renderManager = &renderManager;
    m_window = m_renderManager->getWindow();

    if(!imguiInit()) return false;

    return true;
}

bool GUIManager::shutDown() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    return true;
}

void GUIManager::preRender()
{
    glfwPollEvents();
    if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
    {
        ImGui_ImplGlfw_Sleep(10);
        return;
    }
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GUIManager::postRender()
{
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // Update and Render additional Platform Windows
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
    glfwSwapBuffers(m_window);
}

void GUIManager::showGlobalWindow(bool state) {

    const float WINDOW_AND_STATUS_BAR_HEIGHT = ImGui::GetFrameHeight() * 2.0f;
    const auto &viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(
        ImVec2(viewport->Pos.x, viewport->Pos.y + ImGui::GetFrameHeight()));
    ImGui::SetNextWindowSize(ImVec2(
        // Extract status bar from viewport size
        viewport->Size.x, viewport->Size.y - WINDOW_AND_STATUS_BAR_HEIGHT));
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  
    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
        ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoDocking;
  
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("EugineDockspace", nullptr, flags);
    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);
  
    auto dockspaceId = ImGui::GetID("EugineDockspace");
    ImGui::DockSpace(dockspaceId, ImVec2{0.0f, 0.0f},
                     ImGuiDockNodeFlags_PassthruCentralNode);
  
    if (m_firstTime) {
      ImGui::DockBuilderRemoveNode(dockspaceId);
      ImGui::DockBuilderAddNode(dockspaceId,
                                ImGuiDockNodeFlags_DockSpace |
                                    ImGuiDockNodeFlags_PassthruCentralNode);
      ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);
  
      constexpr float RATIO_1_5 = 0.8f;
      constexpr float RATIO_5_1 = 0.2f;
      constexpr float RATIO_1_4 = 0.25;
  
      ImGuiID topAreaId = -1;
      auto browserId = ImGui::DockBuilderSplitNode(
          dockspaceId, ImGuiDir_Down, RATIO_1_4, nullptr, &topAreaId);
  
      ImGuiID topRightAreaId = -1;
      auto hierarchyId = ImGui::DockBuilderSplitNode(
          topAreaId, ImGuiDir_Left, RATIO_5_1, nullptr, &topRightAreaId);
  
      ImGuiID inspectorId = -1;
      auto viewId = ImGui::DockBuilderSplitNode(topRightAreaId, ImGuiDir_Left,
                                                RATIO_1_5, nullptr, &inspectorId);
  
      ImGui::DockBuilderDockWindow("Hierarchy", hierarchyId);
      ImGui::DockBuilderDockWindow("Inspector", inspectorId);
      ImGui::DockBuilderDockWindow("Viewport", viewId);
      ImGui::DockBuilderDockWindow("Asset Browser", browserId);
  
      ImGui::DockBuilderFinish(dockspaceId);
      m_firstTime = false;
    }
  
    ImGui::End();
}

void GUIManager::showMenuBar(bool state) {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New", "Ctrl+N")) {}
            if (ImGui::MenuItem("Open", "Ctrl+O")) {}
            if (ImGui::MenuItem("Save", "Ctrl+S")) {}
            if (ImGui::MenuItem("Save As..")) {}
            if (ImGui::MenuItem("Exit")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void GUIManager::showViewport(bool state) {
    if (ImGui::Begin("Viewport", &state, 0))
    {
        ImGui::Image(
            m_renderManager->getFrameBuffer()->getTextureColorBuffer(), 
            ImGui::GetContentRegionAvail(),
            ImVec2(0, 1), 
            ImVec2(1, 0)
        );
    }
    ImGui::End();
}

void GUIManager::showSceneHierarchy(bool state) {
    if (ImGui::Begin("Hierarchy", &state, 0))
    {
        ImGui::Text("Hierarchy");
    }
    ImGui::End();
}

void GUIManager::showInspector(bool state) {
    if (ImGui::Begin("Inspector", &state, 0))
    {
        ImGui::Text("Inspector");
    }
    ImGui::End();
}

void GUIManager::showAssetBrowser(bool state) {
    if (ImGui::Begin("Asset Browser", &state, 0))
    {
        ImGui::Text("Asset Browser");
    }
    ImGui::End();
}

bool GUIManager::imguiInit()
{
    if(m_renderManager->getRenderType() == RenderType::OPENGL)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        // Enable docking
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        // Load Fonts
        // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
        // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
        // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
        // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
        // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
        // - Read 'docs/FONTS.md' for more instructions and details.
        // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
        // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
        //io.Fonts->AddFontDefault();
        //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
        //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
        //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
        //IM_ASSERT(font != nullptr);
        return true;
    }

    return false;
}