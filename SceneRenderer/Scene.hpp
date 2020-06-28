# pragma once

#include <sstream>
#include <string>

#include "SceneRenderer/Lights.hpp"
#include "SceneRenderer/Objects.hpp"

namespace SceneRenderer {

class Scene {
    public:
        virtual void initialize() = 0;
        virtual void render() const = 0;

        GlUtils::Camera* camera;
        Scene(GlUtils::Camera* camera) : camera(camera) {}
};


class SimpleScene : public Scene {
    public: 
        std::vector<::SceneRenderer::StaticMaterialObject*> objects;
        std::vector<::SceneRenderer::SimpleLight*> lights;

        void initialize() override {
            ::SceneRenderer::StaticMaterialObject::initShader();
            for(::SceneRenderer::StaticMaterialObject* object : this->objects) {
                object->initialize();
            }
        }

        std::string toString() {
            std::stringstream ss;
            ss << "----- SCENE -----";
            // Lights
            ss << "\n-- LIGHTS --";
            for (int i = 0; i < this->lights.size(); i++) {
                ss << "\n" << i << " - " << this->lights[i]->toString();
            }
            ss << "\n-- OBJECTS --";
            for (int i = 0; i < this->objects.size(); i++) {
                ss << "\n" << i << " - " << this->objects[i]->toString();
            }
            return ss.str();
        }

        void render() const override; 

        void addObject(::SceneRenderer::StaticMaterialObject* object) {
            this->objects.push_back(object);
        }

        void addLight(::SceneRenderer::SimpleLight* light) {
            this->lights.push_back(light);
        }

        SimpleScene(GlUtils::Camera* camera) : ::SceneRenderer::Scene(camera) {}
};

} // namespace SceneRenderer
