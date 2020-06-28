
#include<iostream>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "GlUtils/Camera.hpp"


namespace GlUtils {


// TODO - get pitch/yaw to lookAt origin
Camera::Camera(
    const glm::vec3 origin, 
    const float speed, 
    const float rotateSpeed
) : origin(origin),
    projection(glm::mat4(1.0f))
{
    updateRotation(0.0f, 0.0f);
    // Speed
    setSpeed(speed);
    setRotateSpeed(rotateSpeed);
}

Camera::Camera(
    const glm::vec3 origin, 
    const float pitchDegrees, 
    const float yawDegrees, 
    const float speed, 
    const float rotateSpeed
) : origin(origin),
    pitch(glm::radians(pitchDegrees)),
    yaw(glm::radians(yawDegrees)),
    projection(glm::mat4(1.0f))
{
    updateRotation(0.0f, 0.0f);
    // Speed
    setSpeed(speed);
    setRotateSpeed(rotateSpeed);
}


// TODO - get pitch/yaw to lookAt origin
Camera::Camera(
    // View + movement params
    const glm::vec3 origin, 
    const float speed, 
    const float rotateSpeed,
    // Projection params
    float fovY,
    float aspect,
    float zNear,
    float zFar
) : origin(origin),
    projection(glm::perspective(glm::radians(fovY), aspect, zNear, zFar))
{
    // Rotation
    updateRotation(0.0f, 0.0f);
    // Speed
    setSpeed(speed);
    setRotateSpeed(rotateSpeed);
}


Camera::Camera(
    // View + movement params
    const glm::vec3 origin, 
    const float pitchDegrees, 
    const float yawDegrees, 
    const float speed, 
    const float rotateSpeed,
    // Projection params
    float fovY,
    float aspect,
    float zNear,
    float zFar
) : origin(origin),
    pitch(glm::radians(pitchDegrees)),
    yaw(glm::radians(yawDegrees)),
    projection(glm::perspective(glm::radians(fovY), aspect, zNear, zFar))
{
    // Rotation
    updateRotation(0.0f, 0.0f);
    // Speed
    setSpeed(speed);
    setRotateSpeed(rotateSpeed);
}

void Camera::setSpeed(float speed) {
    if (speed < 0.0f) {
        std::cout 
            << "GlUtils::Camera::setSpeed() - Invalid negative speed value. Setting to 0.0. Value was " 
            << speed 
            << std::endl;
        speed = 0.0f;
    }
    this->speed = speed;
}

void Camera::setRotateSpeed(float rotateSpeed) {
    if (rotateSpeed < 0.0f) {
        std::cout 
            << "GlUtils::Camera::setRotateSpeed() - Invalid negative rotateSpeed value. Setting to 0.0. Value was " 
            << rotateSpeed 
            << std::endl;
        rotateSpeed = 0.0f;
    }
    this->rotateSpeed = rotateSpeed;
}

void Camera::updateRotation(const float deltaPitch, const float deltaYaw) {
    bool rotationChanged = false;
    const float pitchUpdate = deltaPitch * this->rotateSpeed;
    if (abs(pitchUpdate) > 0.0001)
        this->pitch += pitchUpdate;
        rotationChanged = true;
    const float yawUpdate = deltaYaw * this->rotateSpeed;
    if (abs(yawUpdate) > 0.0001) {
        this->yaw += yawUpdate;    
        rotationChanged = true;
    }
    if (rotationChanged) {
        this->forward = glm::normalize(
            glm::vec3(
                cos(this->yaw) * cos(this->pitch),
                sin(this->pitch),
                sin(this->yaw) * cos(this->pitch)
            )
        );
        this->right = glm::cross(this->forward, glm::vec3(0.0f, 1.0f, 0.0f));
        this->up = glm::cross(this->right, this->forward);
    }
}

void Camera::translate(const CameraDirection d, const bool positive, const float deltaTime) {
    const float speedSign = (positive) ? 1.0f : -1.0f;
    if (d == CameraDirection::FORWARD) {
        this->origin += speedSign * this->speed * this->forward;
    } else if (d == CameraDirection::RIGHT) {
        this->origin += speedSign * this->speed * this->right;
    } else if (d == CameraDirection::UP) {
        this->origin += speedSign * this->speed * this->up;
    }
}

glm::vec3 Camera::getOrigin() const {
    return this->origin;
}

float Camera::getPitch() const {
    return this->pitch;
}

float Camera::getYaw() const {
    return this->yaw;
}

glm::mat4 Camera::getView() const {
    return glm::lookAt(this->origin, this->origin + this->forward, this->up);
}

glm::mat4 Camera::getProjection() const {
    return this->projection;
}



glm::vec3 Camera::getForward() const {
    return this->forward;
}

glm::vec3 Camera::getUp() const {
    return this->up;
}

glm::vec3 Camera::getRight() const {
    return this->right;
}

void Camera::standardWalkProcessing(Camera* camera, GLFWwindow* window, const float deltaTime) {
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
        camera->updateRotation(1.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera->updateRotation(-1.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera->updateRotation(0.0f, 1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera->updateRotation(0.0f, -1.0f);
    }
}

} // namespace GlUtils
