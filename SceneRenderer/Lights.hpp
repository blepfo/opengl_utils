#pragma once

#include <glm/glm.hpp>

namespace SceneRenderer {

class SimpleLight {
    public:
        glm::vec3 origin;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 ambient;
        bool isPoint;

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
