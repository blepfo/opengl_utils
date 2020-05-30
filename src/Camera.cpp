
#include<iostream>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "../include/Camera.h"


Camera::Camera(glm::vec3 origin, float pitchDegrees, float yawDegrees, float speed, float rotateSpeed) {
    this->_origin = origin;
    // Rotation
    this->_pitch = glm::radians(pitchDegrees);
    this->_yaw = glm::radians(yawDegrees);
    updateRotation(0.0f, 0.0f);
    // Speed
    setSpeed(speed);
    setRotateSpeed(rotateSpeed);
}


void Camera::setSpeed(float speed) {
    if (speed < 0.0f) {
        std::cout 
            << "Camera::setSpeed - Invalid negative speed value. Setting to 0.0. Value was " 
            << speed 
            << std::endl;
        speed = 0.0f;
    }
    this->_speed = speed;
}

void Camera::setRotateSpeed(float rotateSpeed) {
    if (rotateSpeed < 0.0f) {
        std::cout 
            << "Camera::setRotateSpeed - Invalid negative rotateSpeed value. Setting to 0.0. Value was " 
            << rotateSpeed 
            << std::endl;
        rotateSpeed = 0.0f;
    }
    this->_rotateSpeed = rotateSpeed;
}

void Camera::updateRotation(float deltaPitch, float deltaYaw) {
    bool rotationChanged = false;
    float pitchUpdate = deltaPitch * this->_rotateSpeed;
    if (abs(pitchUpdate) > 0.0001)
        this->_pitch += pitchUpdate;
        rotationChanged = true;
    float yawUpdate = deltaYaw * this->_rotateSpeed;
    if (abs(yawUpdate) > 0.0001) {
        this->_yaw += yawUpdate;    
        rotationChanged = true;
    }
    if (rotationChanged) {
        this->_forward = glm::normalize(
            glm::vec3(
                cos(this->_yaw) * cos(this->_pitch),
                sin(this->_pitch),
                sin(this->_yaw) * cos(this->_pitch)
            )
        );
        this->_right = glm::cross(this->_forward, glm::vec3(0.0f, 1.0f, 0.0f));
        this->_up = glm::cross(this->_forward, this->_right);
    }
}

void Camera::translate(CameraDirection d, bool positive, float deltaTime) {
    float speedSign = (positive) ? 1.0f : -1.0f;
    if (d == CameraDirection::FORWARD) {
        this->_origin += speedSign * this->_speed * this->_forward;
    } else if (d == CameraDirection::RIGHT) {
        this->_origin += speedSign * this->_speed * this->_right;
    } else if (d == CameraDirection::UP) {
        this->_origin += speedSign * this->_speed * this->_up;
    }
}

glm::vec3 Camera::getOrigin() {
    return this->_origin;
}

float Camera::getPitch() {
    return this->_pitch;
}

float Camera::getYaw() {
    return this->_yaw;
}

glm::mat4 Camera::getView() {
    return glm::lookAt(this->_origin, this->_origin + this->_forward, this->_up);
}

glm::vec3 Camera::getForward() {
    return this->_forward;
}

glm::vec3 Camera::getUp() {
    return this->_up;
}

glm::vec3 Camera::getRight() {
    return this->_right;
}

void Camera::standardWalkProcessing(Camera* camera, GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
        std::cout << "ESC KEY -> CLOSE WINDOW" << std::endl;
    }
    // Walk input
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera->translate(CameraDirection::FORWARD, true, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera->translate(CameraDirection::RIGHT, false, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera->translate(CameraDirection::FORWARD, false, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera->translate(CameraDirection::RIGHT, true, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera->translate(CameraDirection::UP, false, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera->translate(CameraDirection::UP, true, deltaTime);
    }
    // Rotation
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera->updateRotation(-1.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera->updateRotation(1.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera->updateRotation(0.0f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera->updateRotation(0.0f, -1.0f);
    }
}
