#include "RendererGLDemo.hpp"
#include "GLFW/glfw3.h"
#include "imgui.h"


Camera RendererGLDemo::m_viewport_camera(glm::vec3(1.0f, 2.0f, 6.0f), glm::vec3(0.f, 1.f, 0.f), -90, -20);
float RendererGLDemo::lastX = 800 / 2.0f;
float RendererGLDemo::lastY = 800 / 2.0f;

bool RendererGLDemo::init()
{
    SCREEN_WIDTH = std::stoi(m_configManager->getEngineOption("renderer", "screen_width"));
    SCREEN_HEIGHT = std::stoi(m_configManager->getEngineOption("renderer", "screen_height"));
    RendererGLDemo::lastX = SCREEN_WIDTH / 2.0f;
    RendererGLDemo::lastY = SCREEN_HEIGHT / 2.0f;

    glEnable(GL_DEPTH_TEST);

    glfwSetCursorPosCallback(m_window, mouseCallback);
    glfwSetScrollCallback(m_window, scrollCallback);
    
    return true;
}

bool RendererGLDemo::deinit()
{
    return true;
}

void RendererGLDemo::render()
{
    processInput(m_window);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    objSh.use();

    //setting up camera
    glm::mat4 projection = glm::perspective(glm::radians(RendererGLDemo::m_viewport_camera.getZoom()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f);
    glm::mat4 view = RendererGLDemo::m_viewport_camera.getViewMatrix();
    objSh.setMat4("projection", projection);
    objSh.setMat4("view", view);
	
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
    model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));
    objSh.setMat4("model", model);
    modelDemo.draw(objSh);
}

RendererGLDemo::~RendererGLDemo()
{
}

void RendererGLDemo::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        RendererGLDemo::m_viewport_camera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        RendererGLDemo::m_viewport_camera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        RendererGLDemo::m_viewport_camera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        RendererGLDemo::m_viewport_camera.processKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void RendererGLDemo::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
    static bool firstMouse = true;

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;
    if(ImGui::IsMouseDown(ImGuiMouseButton_Right))
	    m_viewport_camera.processMouseMovement(xoffset, yoffset, window);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void RendererGLDemo::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_viewport_camera.processMouseScroll(static_cast<float>(yoffset));
}