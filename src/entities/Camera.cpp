//
// Created by Msi on 10/25/2023.
//

#include "Camera.h"
#include "GLFW/glfw3.h"

namespace starlight {
    Camera::Camera() {

    }

    glm::vec3 Camera::getPosition() {
        return position;
    }

    float Camera::getPitch() {
        return pitch;
    }

    float Camera::getYaw() {
        return yaw;
    }

    float Camera::getRoll() {
        return roll;
    }

    void Camera::move(int key) {
        if(key==GLFW_KEY_W){
            position.z-=0.2f;
        }
        if(key==GLFW_KEY_S){
            position.z+=0.2f;
        }
        if(key==GLFW_KEY_A){
            position.x-=0.2f;
        }
        if(key==GLFW_KEY_D){
            position.x+=0.2f;
        }
    }

    Camera::Camera(glm::vec3 position, float yaw, float pitch) {
        this->position=position;
        this->yaw=yaw;
        this->pitch=pitch;
    }
} // starlight