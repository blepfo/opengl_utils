#ifndef _CAMERA_H
#define _CAMERA_H

#include<glm/glm.hpp>

enum class CameraDirection {
    FORWARD, 
    RIGHT,
    UP
};

class Camera {
    public:
        Camera(
            glm::vec3 origin, 
            float pitchDegrees, 
            float yawDegrees, 
            float speed, 
            float rotateSpeed
        );

        void translate(CameraDirection d, bool positive, float deltaTime);
        void setSpeed(float speed);
        void setRotateSpeed(float rotateSpeed);
        void updateRotation(float deltaPitch, float deltaYaw);
        glm::mat4 getView();
        glm::vec3 getOrigin();
        float getPitch();
        float getYaw();

    private:
        float _pitch;
        float _yaw;
        float _speed;
        float _rotateSpeed;
        glm::vec3 _origin;
        glm::vec3 _forward;
        glm::vec3 _up;
        glm::vec3 _right;

};

#endif
