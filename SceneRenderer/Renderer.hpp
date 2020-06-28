#pragma once

#include <vector>

#include "GlUtils/SimpleRenderer.hpp"

#include "SceneRenderer/Scene.hpp"


namespace SceneRenderer {

class Renderer : public ::GlUtils::SimpleRenderer {
    public: 
        ::SceneRenderer::Scene* scene;

        // Overrides for GlUtils::SimpleRenderer
        void initScene() override {
            this->scene->initialize();
        };

        void renderObjects() override {
            this->scene->render();
        };

        Renderer(
            ::SceneRenderer::Scene* scene,
            const int screenWidth,
            const int screenHeight,
            const char* windowName,
            const bool useImgui = true
        ) : GlUtils::SimpleRenderer(screenWidth, screenHeight, windowName, useImgui), 
            scene(scene) {}

};

} // namespace SceneRenderer
