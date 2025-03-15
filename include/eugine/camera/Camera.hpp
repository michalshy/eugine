#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "TypeDef.hpp"
#include <glad/glad.h>
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
    glm::vec3 Postion;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    //Euler Angles
    float Yaw;
    float Pitch;
    //Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
public:
    /**
     * @brief Construct a new Camera object
     * with vectors
     */
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW,
        float pitch = PITCH
    ) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY),
        Zoom(ZOOM)
    {
        Postion = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    /**
     * @brief Construct a new Camera object
     * with scalar values
     */
    Camera(
        float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch
    ) : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY),
        Zoom(ZOOM)
    {
        Postion = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    //Getter of view matrix
    glm::mat4 getViewMatrix()
    {
        return glm::lookAt(Postion, Postion + Front, Up);
    }
    //Standard getters
    glm::vec3 getPosition(){ return Postion; }
    glm::vec3 getFront(){ return Front; }
    glm::vec3 getUp(){ return Up; }
    glm::vec3 getRight(){ return Right; }
    glm::vec3 getWorldUp(){ return WorldUp; }
    float getYaw(){ return Yaw; }
    float getPitch(){ return Pitch; }
    float getMovementSpeed(){ return MovementSpeed; }
    float getMouseSensitivity(){ return MouseSensitivity; }
    float getZoom(){ return Zoom; }

    void processKeyboard(CameraMovement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if(direction == FORWARD)
            Postion += Front * velocity;
        if(direction == BACKWARD)
            Postion -= Front * velocity;
        if(direction == LEFT)
            Postion -= Right * velocity;
        if(direction == RIGHT)
            Postion += Right * velocity;
    }
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;
        Yaw += xoffset;
        Pitch += yoffset;
        if(constrainPitch)
        {
            if(Pitch > 89.0f)
                Pitch = 89.0f;
            if(Pitch < -89.0f)
                Pitch = -89.0f;
        }
        updateCameraVectors();
    }
    void processMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if(Zoom < 1.0f)
            Zoom = 1.0f;
        if(Zoom > 45.0f)
            Zoom = 45.0f;
    }
private:
    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif // CAMERA_HPP