#pragma once

#include<GLFW/glfw3.h>
#include<glm/glm.hpp>


namespace GlUtils {

enum class CameraDirection {
    FORWARD, 
    RIGHT,
    UP
};

class Camera {
    public:
        // Constructor for no  
        Camera(
            glm::vec3 origin, 
            float pitchDegrees, 
            float yawDegrees, 
            float speed, 
            float rotateSpeed
        ); 

        Camera(
            // View + movement params
            glm::vec3 origin, 
            float pitchDegrees, 
            float yawDegrees, 
            float speed, 
            float rotateSpeed,
            // Perspective Params
            float fovY,
            float aspect, 
            float zNear,
            float zFar
        ); 

        void translate(const CameraDirection d, const bool positive, const float deltaTime);
        void setSpeed(float speed);
        void setRotateSpeed(float rotateSpeed);
        void updateRotation(const float deltaPitch, const float deltaYaw);
        glm::mat4 getView() const;
        glm::mat4 getProjection() const;
        glm::vec3 getOrigin() const;
        glm::vec3 getForward() const;
        glm::vec3 getUp() const;
        glm::vec3 getRight() const;
        float getPitch() const;
        float getYaw() const;

        static void standardWalkProcessing(Camera* camera, GLFWwindow* window, float deltaTime);

    private:
        float _pitch;
        float _yaw;
        float _speed;
        float _rotateSpeed;
        glm::vec3 _origin;
        glm::vec3 _forward;
        glm::vec3 _up;
        glm::vec3 _right;
        glm::mat4 projection;
};

} // namespace GlUtils
