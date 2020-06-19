# pragma once

#include "SceneRenderer/Lights.hpp"
#include "SceneRenderer/Objects.hpp"

namespace SceneRenderer {

class Scene {
    virtual void initialize() = 0;
    virtual void render() = 0;
}

class SimpleScene : public Scene {
    std::vector<::SceneRenderer::StaticMaterialObject*> objects;
    std::vector<::SceneRenderer::SimpleLight*> lights;
    GlUtils::Camera* camera;

    void initialize override () {
        for(::SceneRenderer::StaticMaterialObject* object : this->objects) {
            object->initialise();
        }
    }

    void render override(); 

    void addObject(::SceneRenderer::StaticMaterialObject* object) {
        this->objects.push_back(object);
    }

    void addLight(::SceneRenderer::Light light) {
        this->lights.push_back(light);
    }
}

} // namespace SceneRenderer
