#pragma once

#include <glm/glm.hpp>

#include "GlUtils/Shader.hpp"


namespace SceneRenderer {

class StaticMaterial {
    public:
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 ambient;
        glm::vec3 emission;
        float shiny;

        StaticMaterial(glm::vec3 emission) 
            : diffuse(glm::vec3(0.0f)), 
              specular(glm::vec3(0.0f)), 
              ambient(glm::vec3(0.0f)), 
              emission(glm::vec3(emission)), 
              shiny(0.0f) {}

        StaticMaterial(
            glm::vec3 diffuse,
            glm::vec3 specular,
            float shiny
        ) : diffuse(diffuse),
            specular(specular),
            shiny(shiny),
            ambient(glm::vec3(0.0f)),
            emission(glm::vec3(0.0f)) {}

        StaticMaterial(
            glm::vec3 diffuse,
            glm::vec3 specular,
            glm::vec3 ambient,
            float shiny
        ) : diffuse(diffuse),
            specular(specular),
            ambient(ambient),
            shiny(shiny),
            emission(glm::vec3(0.0f)) {}

        StaticMaterial(
            glm::vec3 diffuse,
            glm::vec3 specular,
            glm::vec3 ambient,
            glm::vec3 emission,
            float shiny
        ) : diffuse(diffuse),
            specular(specular),
            ambient(ambient),
            shiny(shiny),
            emission(emission) {}
            
};

} // namespace SceneRenderer
