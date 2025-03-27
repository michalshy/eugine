#include "RendererGLDemo.hpp"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "renderer/FrameBuffer.hpp"

Camera RendererGLDemo::viewportCamera(glm::vec3(1.0f, 2.0f, 6.0f), glm::vec3(0.f, 1.f, 0.f), -90, -20);
float RendererGLDemo::lastX = 800 / 2.0f;
float RendererGLDemo::lastY = 800 / 2.0f;

bool RendererGLDemo::Init()
{
    screenWidth = std::stoi(configManager->GetEngineOption("renderer", "screen_width"));
    screenWidth = std::stoi(configManager->GetEngineOption("renderer", "screen_height"));
    RendererGLDemo::lastX = screenWidth / 2.0f;
    RendererGLDemo::lastY = screenWidth / 2.0f;
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    glEnable(GL_DEPTH_TEST);

    screenShader.Use();
    screenShader.SetInt("screenTexture", 0);

    frameBuffer.Configure();

    return true;
}

bool RendererGLDemo::Deinit()
{
    return true;
}

void RendererGLDemo::Render()
{
    ProcessInput(window);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    frameBuffer.Bind();

    objectShader.Use();
    //setting up camera
    glm::mat4 projection = glm::perspective(glm::radians(RendererGLDemo::viewportCamera.GetZoom()), (float)800 / (float)600, 0.1f, 100.f);
    glm::mat4 view = RendererGLDemo::viewportCamera.GetViewMatrix();
    objectShader.SetMat4("projection", projection);
    objectShader.SetMat4("view", view);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
    model = glm::scale(model, glm::vec3(1.f, 1.f, 1.f));
    objectShader.SetMat4("model", model);

    // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
    // clear all relevant buffers
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
    glClear(GL_COLOR_BUFFER_BIT);

    screenShader.Use();
    frameBuffer.DrawToTexture();
}

FrameBuffer* RendererGLDemo::GetFrameBuffer()
{
    return &frameBuffer;
}

RendererGLDemo::~RendererGLDemo()
{
}

void RendererGLDemo::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        RendererGLDemo::viewportCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        RendererGLDemo::viewportCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        RendererGLDemo::viewportCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        RendererGLDemo::viewportCamera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void RendererGLDemo::MouseCallback(GLFWwindow* window, double xposIn, double yposIn)
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
	    viewportCamera.ProcessMouseMovement(xoffset, yoffset, window);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void RendererGLDemo::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	viewportCamera.ProcessMouseScroll(static_cast<float>(yoffset));
}
