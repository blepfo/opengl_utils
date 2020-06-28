#pragma once

#include <sstream>
#include <string>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace SceneRenderer {

class SimpleLight {
    public:
        glm::vec3 origin;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 ambient;
        bool isPoint;

        virtual std::string toString() const = 0;

        SimpleLight(
            glm::vec3 origin,
            glm::vec3 diffuse,
            glm::vec3 specular,
            bool isPoint
        ) : origin(origin), 
            diffuse(diffuse), 
            specular(specular), 
            ambient(glm::vec3(0.0f)), 
            isPoint(isPoint) {}

        SimpleLight(
            glm::vec3 origin,
            glm::vec3 diffuse,
            glm::vec3 specular,
            glm::vec3 ambient,
            bool isPoint
        ) : origin(origin), 
            diffuse(diffuse), 
            specular(specular), 
            ambient(ambient), 
            isPoint(isPoint) {}
};


class PointLight : public ::SceneRenderer::SimpleLight {
    public:
        std::string toString() const override {
            std::stringstream ss;
            ss 
                << "SceneRenderer::PointLight\n"
                << "\torigin=(" << this->origin[0] << ", " << this->origin[1] << ", " << this->origin[2] << ")\n"
                << "\tdiffuse=(" << this->diffuse[0] << ", " << this->diffuse[1] << ", " << this->diffuse[2] << ")\n"
                << "\tspecular=(" << this->specular[0] << ", " << this->specular[1] << ", " << this->specular[2] << ")\n"
                << "\tambient=(" << this->ambient[0] << ", " << this->ambient[1] << ", " << this->ambient[2] << ")\n"
            ;
            return ss.str();
        }

        PointLight(
            glm::vec3 origin,
            glm::vec3 diffuse,
            glm::vec3 specular
        ) : ::SceneRenderer::SimpleLight(origin, diffuse, specular, true) {}

        PointLight(
            glm::vec3 origin,
            glm::vec3 diffuse,
            glm::vec3 specular,
            glm::vec3 ambient
        ) : ::SceneRenderer::SimpleLight(origin, diffuse, specular, ambient, true) {}

};


class DirectionLight : public ::SceneRenderer::SimpleLight {
    public:
        std::string toString() const override {
            std::stringstream ss;
            ss 
                << "SceneRenderer::PointLight\n"
                << "\torigin=(" << this->origin[0] << ", " << this->origin[1] << ", " << this->origin[2] << ")\n"
                << "\tdiffuse=(" << this->diffuse[0] << ", " << this->diffuse[1] << ", " << this->diffuse[2] << ")\n"
                << "\tspecular=(" << this->specular[0] << ", " << this->specular[1] << ", " << this->specular[2] << ")\n"
                << "\tambient=(" << this->ambient[0] << ", " << this->ambient[1] << ", " << this->ambient[2] << ")\n"
            ;
            return ss.str();
        }

        DirectionLight(
            glm::vec3 origin,
            glm::vec3 diffuse,
            glm::vec3 specular
        ) : ::SceneRenderer::SimpleLight(origin, diffuse, specular, false) {}

        DirectionLight(
            glm::vec3 origin,
            glm::vec3 diffuse,
            glm::vec3 specular,
            glm::vec3 ambient
        ) : ::SceneRenderer::SimpleLight(origin, diffuse, specular, ambient, false) {}

};
    
} // namespace SceneRenderer
