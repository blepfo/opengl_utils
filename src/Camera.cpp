
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
    this->_pitch += deltaPitch * this->_rotateSpeed;
    this->_yaw += deltaYaw * this->_rotateSpeed;
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

float Camera::getPitch() {
    return this->_pitch;
}

float Camera::getYaw() {
    return this->_yaw;
}

glm::mat4 Camera::getView() {
    return glm::lookAt(this->_origin, this->_origin + this->_forward, this->_up);
}
