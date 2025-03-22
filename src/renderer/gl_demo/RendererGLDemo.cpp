#include "RendererGLDemo.hpp"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "renderer/FrameBuffer.hpp"

Camera RendererGLDemo::m_viewport_camera(glm::vec3(1.0f, 2.0f, 6.0f), glm::vec3(0.f, 1.f, 0.f), -90, -20);
float RendererGLDemo::lastX = 800 / 2.0f;
float RendererGLDemo::lastY = 800 / 2.0f;

bool RendererGLDemo::init()
{
    m_screenWidth = std::stoi(m_configManager->getEngineOption("renderer", "screen_width"));
    m_screenWidth = std::stoi(m_configManager->getEngineOption("renderer", "screen_height"));
    RendererGLDemo::lastX = m_screenWidth / 2.0f;
    RendererGLDemo::lastY = m_screenWidth / 2.0f;
    glfwSetCursorPosCallback(m_window, mouseCallback);
    glfwSetScrollCallback(m_window, scrollCallback);

    glEnable(GL_DEPTH_TEST);

    m_screenShader.use();
    m_screenShader.setInt("screenTexture", 0);

    m_frameBuffer.configure();

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
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    m_frameBuffer.bind();

    m_objSh.use();
    //setting up camera
    glm::mat4 projection = glm::perspective(glm::radians(RendererGLDemo::m_viewport_camera.getZoom()), (float)800 / (float)600, 0.1f, 100.f);
    glm::mat4 view = RendererGLDemo::m_viewport_camera.getViewMatrix();
    m_objSh.setMat4("projection", projection);
    m_objSh.setMat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
    model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));
    m_objSh.setMat4("model", model);
    m_modelDemo.draw(m_objSh);

    // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    // clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);

    m_screenShader.use();
    m_frameBuffer.drawToTexture();
}

FrameBuffer* RendererGLDemo::getFrameBuffer()
{
    return &m_frameBuffer;
}

RendererGLDemo::~RendererGLDemo()
{
}

void RendererGLDemo::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        RendererGLDemo::m_viewport_camera.processKeyboard(FORWARD, m_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        RendererGLDemo::m_viewport_camera.processKeyboard(BACKWARD, m_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        RendererGLDemo::m_viewport_camera.processKeyboard(LEFT, m_deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        RendererGLDemo::m_viewport_camera.processKeyboard(RIGHT, m_deltaTime);
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
