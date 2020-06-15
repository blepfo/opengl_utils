#pragma once

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include "GlUtils/SimpleRenderer.hpp"

namespace GlUtils {

class TwoTrianglesRenderer : public ::GlUtils::SimpleRenderer {
    public: 
        // Set uniforms for each frame
        virtual void setUniforms() = 0;

        void initScene();
        void renderObjects();

        TwoTrianglesRenderer(
			const char* fragmentShaderPath,
            const int screenWidth,
            const int screenHeight,
            const char* windowName,
            const bool useImgui=true
        ) : fragmentShaderPath(fragmentShaderPath),
            SimpleRenderer(screenWidth, screenHeight, windowName, useImgui) {}

    protected:
        // TODO - SceneObject class
        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;
        Shader* shader;

        const char* fragmentShaderPath;
};

} // namespace GlUtils
