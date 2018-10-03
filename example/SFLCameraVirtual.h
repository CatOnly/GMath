#ifndef SFLCAMERAVIRTUAL_H
#define SFLCAMERAVIRTUAL_H

#include "GMath.hpp"

#define Camera_Yaw        0.0
#define Camera_Pitch      0.0
#define Camera_Speed      3.0
#define Camera_Sensitivty 0.01
#define Camera_Zoom       45.0


class SFLCameraVirtual
{
public:
    enum SFLCameraMove{
        moveForward,
        moveBackward,
        moveRight,
        moveLeft
    };

    float moveSpeed;
    float mouseSensitivity;

    gm::vec3 position;
    gm::vec3 axisRight;
    gm::vec3 axisUp;
    gm::vec3 axisFront;

    float currentZoom;
    float currentYaw;
    float currentPich;

    SFLCameraVirtual(glm::vec3 beginPosition, glm::vec3 worldUp = glm::vec3(0.0, 1.0, 0.0), GLfloat beginYaw = Camera_Yaw, GLfloat beginPich = Camera_Pitch) {
        _worldUp = worldUp;
        _defaultPosition = beginPosition;
        _defaultYaw = beginYaw;
        _defaultPich = beginPich;

        position = beginPosition;
        currentYaw = beginYaw;
        currentPich = beginPich;

        currentZoom = Camera_Zoom;
        moveSpeed = Camera_Speed;
        mouseSensitivity = Camera_Sensitivty;

        updateCameraVectors();
    }

    void resetData(){
        position = _defaultPosition;
        currentYaw = _defaultYaw;
        currentPich = _defaultPich;

        currentZoom = Camera_Zoom;

        updateCameraVectors();
    }

    void moveStepFromDirection(SFLCameraMove direction, GLfloat deltaTime = 0.1) {
        GLfloat velocity = moveSpeed * deltaTime;

        switch (direction) {
        case moveForward:
            position += axisFront * velocity;
            break;
        case moveBackward:
            position -= axisFront * velocity;
            break;
        case moveLeft:
            position -= axisRight * velocity;
            break;
        case moveRight:
            position += axisRight * velocity;
            break;
        }
    }

    void rotateByMouseOffset(GLfloat offsetX, GLfloat offsetY, GLboolean constrainPitch = true) {
        offsetX *= mouseSensitivity;
        offsetY *= mouseSensitivity;

        if (abs(offsetX) > abs(offsetY)){
            currentYaw  += offsetX;
        } else {
            currentPich += offsetY;
        }

        if (constrainPitch) {
            if (currentPich > 89.0f)
                currentPich = 89.0f;
            if (currentPich < -89.0f)
                currentPich = -89.0f;
        }

        updateCameraVectors();
    }

    glm::mat4 viewMatrix() {
        return glm::lookAt(position, position + axisFront, axisUp);
    }

private:
    glm::vec3 _worldUp;
    glm::vec3 _defaultPosition;
    float _defaultYaw;
    float _defaultPich;

    void updateCameraVectors(){
        glm::vec3 front;
        front.x =  sin(glm::radians(currentYaw)) * cos(glm::radians(currentPich));
        front.y =  sin(glm::radians(currentPich));
        front.z = -cos(glm::radians(currentYaw)) * cos(glm::radians(currentPich));

        axisFront = glm::normalize(front);
        axisRight = glm::normalize(glm::cross(axisFront, _worldUp));
        axisUp    = glm::normalize(glm::cross(axisRight, axisFront));
    }

};


#endif // SFLCAMERAVIRTUAL_H
