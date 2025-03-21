#include "RenderManager.hpp"
#include "GLFW/glfw3.h"
#include "gl_renderer/FrameBuffer.hpp"
#include "imgui.h"

RenderManager::RenderManager()
{
    //Do nothing
}

RenderManager::~RenderManager()
{
    //Do nothing
}

bool RenderManager::startUp()
{
    //initialize glad, opengl, glfw
    if(!lowLevelInit()) return false;
    //check for renderer
    if(!chooseRenderer()) return false;
    //initialize renderer
    if(!m_renderer->init()) return false;
    //initialize imgui
    if(!imguiInit()) return false;
    return true;
}

bool RenderManager::shutDown()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // Cleanup glfw
    glfwDestroyWindow(m_window);
    glfwTerminate();
    //Clear stack allocator
    m_allocator.clear();
    return true;
}

void RenderManager::setConfig(ConfigManager& configManager)
{
    m_configManager = &configManager;
}

void RenderManager::render()
{
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while(!glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(m_window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        m_renderer->render();
        m_guiManager->createGUI();
        //Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
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
}

bool RenderManager::lowLevelInit()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Create window
    m_window = glfwCreateWindow(800, 600, "EUGINE", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync
    // Setup GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to init GLAD" << std::endl;
        return false;
    }
    m_screenHeight = std::stoi(m_configManager->getEngineOption("renderer", "screen_height"));
    m_screenWidth = std::stoi(m_configManager->getEngineOption("renderer", "screen_width"));
    glViewport(0, 0, m_screenWidth, m_screenHeight);

    return true;
}

bool RenderManager::imguiInit()
{
    if(m_rType == RenderType::OPENGL)
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

bool RenderManager::chooseRenderer()
{
    //Define type
    std::string type = m_configManager->getEngineOption("renderer", "type");
    if(type == "opengl")
        m_rType = RenderType::OPENGL;
    else if(type == "directx")
        m_rType = RenderType::DIRECTX;
    else 
        m_rType = RenderType::OPENGL;

    //check if demo or real renderer is loaded
    std::string isDemo = m_configManager->getEngineOption("renderer", "demo");
    
    if(m_rType == RenderType::OPENGL)
    {
        //check if demo should be played
        if(isDemo == "y")
        {
            //allocate memory for demo renderer
            void* addr = m_allocator.alloc(sizeof(RendererGLDemo));
            if(addr != nullptr) //if success
            {
                //allocate new object at address
                //IMPORTANT: THIS IS NOT SYSCALL
                m_renderer = new (addr) RendererGLDemo(*m_configManager, m_window);
            }
            else 
            {
                return false;
            }
        }
        else
        {
            //allocate memory for standard OpenGL renderer
            void* addr = m_allocator.alloc(sizeof(RendererGL));
            if(addr != nullptr)
                //allocate new object at address
                //IMPORTANT: THIS IS NOT SYSCALL
                m_renderer = new (addr) RendererGL(*m_configManager);
            else
                return false;
        }
    }
    else if(m_rType == RenderType::DIRECTX) //check for direct, other instructions are the same
    {
        void* addr = m_allocator.alloc(sizeof(RendererDX));
        if(addr != nullptr)
            m_renderer = new (addr) RendererDX();
        else
            return false;
    }
    else
    {
        return false;
    }

    return true;
}
