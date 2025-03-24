#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

//Default values
constexpr float YAW = -90.0f;
constexpr float PITCH = -90.0f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.0f;

class Camera
{
    //Camera Attributes
    glm::vec3 postion;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    //Euler Angles
    float yaw;
    float pitch;
    //Camera options
    float movementSpeed;
    float mouseSensitivity;
    float zoom;
public:
    /**
     * @brief Construct a new Camera object
     * with vectors
     */
    Camera(
        glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f),
        float _yaw = YAW,
        float _pitch = PITCH
    ) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed(SPEED),
        mouseSensitivity(SENSITIVITY),
        zoom(ZOOM)
    {
        postion = _position;
        worldUp = _up;
        yaw = _yaw;
        pitch = _pitch;
        UpdateCameraVectors();
    }

    /**
     * @brief Construct a new Camera object
     * with scalar values
     */
    Camera(
        float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float _yaw, float _pitch
    ) : front(glm::vec3(0.0f, 0.0f, -1.0f)),
        movementSpeed(SPEED),
        mouseSensitivity(SENSITIVITY),
        zoom(ZOOM)
    {
        postion = glm::vec3(posX, posY, posZ);
        worldUp = glm::vec3(upX, upY, upZ);
        yaw = _yaw;
        pitch = _pitch;
        UpdateCameraVectors();
    }
    //Getter of view matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(postion, postion + front, up);
    }
    //Standard getters
    glm::vec3 GetPosition(){ return postion; }
    glm::vec3 GetFront(){ return front; }
    glm::vec3 GetUp(){ return up; }
    glm::vec3 GetRight(){ return right; }
    glm::vec3 GetWorldUp(){ return worldUp; }
    float GetYaw(){ return yaw; }
    float GetPitch(){ return pitch; }
    float GetMovementSpeed(){ return movementSpeed; }
    float GetMouseSensitivity(){ return mouseSensitivity; }
    float GetZoom(){ return zoom; }

    void ProcessKeyboard(CameraMovement direction, float deltaTime)
    {
        float velocity = movementSpeed * deltaTime;
        if(direction == FORWARD)
            postion += front * velocity;
        if(direction == BACKWARD)
            postion -= front * velocity;
        if(direction == LEFT)
            postion -= right * velocity;
        if(direction == RIGHT)
            postion += right * velocity;
    }
    void ProcessMouseMovement(float xoffset, float yoffset, GLFWwindow* window, GLboolean constrainPitch = true)
    {
        xoffset *= mouseSensitivity;
        yoffset *= mouseSensitivity;
        yaw += xoffset;
        pitch += yoffset;
        if(constrainPitch)
        {
            if(pitch > 89.0f)
                pitch = 89.0f;
            if(pitch < -89.0f)
                pitch = -89.0f;
        }
        UpdateCameraVectors();
    }
    void ProcessMouseScroll(float yoffset)
    {
        zoom -= (float)yoffset;
        if(zoom < 1.0f)
            zoom = 1.0f;
        if(zoom > 45.0f)
            zoom = 45.0f;
    }
private:
    void UpdateCameraVectors()
    {
        glm::vec3 _front;
        _front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        _front.y = sin(glm::radians(pitch));
        _front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(_front);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};

#endif // CAMERA_HPP