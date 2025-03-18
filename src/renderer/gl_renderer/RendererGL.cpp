#include "RendererGL.hpp"

Camera RendererGL::m_viewport_camera(glm::vec3(1.0f, 2.0f, 6.0f), glm::vec3(0.f, 1.f, 0.f), -90, -20);
float RendererGL::lastX = 800 / 2.0f;
float RendererGL::lastY = 800 / 2.0f;
static Shader objSh("../res/default/shaders/sh.vert", "../res/default/shaders/sh.frag");
static Shader lghtSh("../res/default/shaders/shL.vert", "../res/default/shaders/shL.frag");
static glm::vec3 pointLightPositions[] =
{
	glm::vec3(0.7f, 0.2f, 2.0f),
	glm::vec3(2.3f, -3.3f, -4.0f),
	glm::vec3(-4.f, 2.0f, -12.0f),
	glm::vec3(0.f, 0.0f, -3.0f)
};

static constexpr glm::vec3 cubePositions[] =
{
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
};

bool RendererGL::init()
{
    SCREEN_WIDTH = std::stoi(m_configManager->getEngineOption("renderer", "screen_width"));
    SCREEN_HEIGHT = std::stoi(m_configManager->getEngineOption("renderer", "screen_height"));

    if(m_configManager->getEngineOption("engine", "demo") == "y")
    {
        m_demo = true;
    }
    if(m_demo);
        initDefault();

    return true;
}

bool RendererGL::deinit()
{
    return true;
}

void RendererGL::render()
{
    if(m_demo)
        renderDefault();
}

RendererGL::~RendererGL()
{
}

u32 RendererGL::loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrChannels;
	unsigned char* data;
	data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		std::cout << "Failed to load tex" << std::endl;
	}
	stbi_image_free(data);
	return textureID;
}

void RendererGL::initDefault()
{
    RendererGL::lastX = SCREEN_WIDTH / 2.0f;
    RendererGL::lastY = SCREEN_HEIGHT / 2.0f;
    m_demoStruct.tDiffuse = loadTexture("./res/default/textures/container2.png");
    m_demoStruct.tSpecular = loadTexture("./res/default/textures/container2_specular.png");
    float vertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };

    glGenBuffers(1, &m_demoStruct.VBO);
    glGenVertexArrays(1, &m_demoStruct.objectVAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_demoStruct.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(m_demoStruct.objectVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &m_demoStruct.lightVAO);
    glBindVertexArray(m_demoStruct.lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_demoStruct.VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    objSh.use();
    //attach texture
    objSh.setInt("material.diffuse", 0);
    objSh.setInt("material.specular", 1);
    objSh.setInt("material.emission", 2);
    objSh.setFloat("material.shininess", 32.0f);

    glEnable(GL_DEPTH_TEST);

    glfwSetCursorPosCallback(m_window, mouseCallback);
    glfwSetScrollCallback(m_window, scrollCallback);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void RendererGL::renderDefault()
{
    processInput(m_window);

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    objSh.use();

    //setting lights
    objSh.setVec3("viewPos", RendererGL::m_viewport_camera.getPosition());
    //point

    //directional
    objSh.setVec3("dirLight.direction", -0.2f, -1.f, -0.3f);
    objSh.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
    objSh.setVec3("dirLight.diffuse", 0.2f, 0.2f, 0.2f); // darken diffuse light a bit
    objSh.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);

    //spotlight
    objSh.setVec3("spotLight.position", RendererGL::m_viewport_camera.getPosition());
    objSh.setVec3("spotLight.direction", RendererGL::m_viewport_camera.getFront());
    objSh.setVec3("spotLight.ambient", 0.1f, 0.1f, 0.1f);
    objSh.setVec3("spotLight.diffuse", 0.8f, 0.8f, 0.8f); // darken diffuse light a bit
    objSh.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    objSh.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    objSh.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(20.f)));
    objSh.setFloat("spotLight.constant", 1.0f);
    objSh.setFloat("spotLight.linear", 0.09f);
    objSh.setFloat("spotLight.quadratic", 0.032f);

    //for point light
    objSh.setVec3("pointLights[0].position", pointLightPositions[0]);
    objSh.setVec3("pointLights[0].ambient", 0.1f, 0.1f, 0.1f);
    objSh.setVec3("pointLights[0].diffuse", 0.4f, 0.4f, 0.4f); // darken diffuse light a bit
    objSh.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    objSh.setFloat("pointLights[0].constant", 1.0f);
    objSh.setFloat("pointLights[0].linear", 0.09f);
    objSh.setFloat("pointLights[0].quadratic", 0.032f);
    objSh.setVec3("pointLights[1].position", pointLightPositions[1]);
    objSh.setVec3("pointLights[1].ambient", 0.1f, 0.1f, 0.1f);
    objSh.setVec3("pointLights[1].diffuse", 0.4f, 0.4f, 0.4f); // darken diffuse light a bit
    objSh.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    objSh.setFloat("pointLights[1].constant", 1.0f);
    objSh.setFloat("pointLights[1].linear", 0.09f);
    objSh.setFloat("pointLights[1].quadratic", 0.032f);
    objSh.setVec3("pointLights[2].position", pointLightPositions[2]);
    objSh.setVec3("pointLights[2].ambient", 0.1f, 0.1f, 0.1f);
    objSh.setVec3("pointLights[2].diffuse", 0.4f, 0.4f, 0.4f); // darken diffuse light a bit
    objSh.setVec3("pointLights[2].specular", 0.8f, 0.8, 0.8);
    objSh.setFloat("pointLights[2].constant", 1.0f);
    objSh.setFloat("pointLights[2].linear", 0.09f);
    objSh.setFloat("pointLights[2].quadratic", 0.032f);
    objSh.setVec3("pointLights[3].position", pointLightPositions[3]);
    objSh.setVec3("pointLights[3].ambient", 0.1f, 0.1f, 0.1f);
    objSh.setVec3("pointLights[3].diffuse", 0.3f, 0.3f, 0.3f); // darken diffuse light a bit
    objSh.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    objSh.setFloat("pointLights[3].constant", 1.0f);
    objSh.setFloat("pointLights[3].linear", 0.09f);
    objSh.setFloat("pointLights[3].quadratic", 0.032f);


    //setting up camera
    glm::mat4 projection = glm::perspective(glm::radians(RendererGL::m_viewport_camera.getZoom()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f);
    glm::mat4 view = RendererGL::m_viewport_camera.getViewMatrix();
    objSh.setMat4("projection", projection);
    objSh.setMat4("view", view);

    //rotation and translation
    glm::mat4 model = glm::mat4(1.f);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_demoStruct.tDiffuse);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_demoStruct.tSpecular);

    for (unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.f, 0.3f, 0.5f));
        objSh.setMat4("model", model);
        glBindVertexArray(m_demoStruct.objectVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    //draw light
    lghtSh.use();
    lghtSh.setMat4("projection", projection);
    lghtSh.setMat4("view", view);

    for (int i = 0; i < 4; i++)
    {

        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lghtSh.setMat4("model", model);
        glBindVertexArray(m_demoStruct.lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    glBindVertexArray(0);
}

void RendererGL::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        RendererGL::m_viewport_camera.processKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        RendererGL::m_viewport_camera.processKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        RendererGL::m_viewport_camera.processKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        RendererGL::m_viewport_camera.processKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void RendererGL::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
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

	m_viewport_camera.processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void RendererGL::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	m_viewport_camera.processMouseScroll(static_cast<float>(yoffset));
}