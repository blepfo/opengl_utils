#ifndef _TWO_TRIANGLES_RENDERER_H
#define _TWO_TRIANGLES_RENDERER_H


#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include "./SimpleRenderer.h"

class TwoTrianglesRenderer : public SimpleRenderer {
    public: 
        // Set uniforms for each frame
        virtual void setUniforms() = 0;

        void initScene();
        void renderObjects();

        TwoTrianglesRenderer(
			const char* fragmentShaderPath,
            int screenWidth,
            int screenHeight,
            const char* windowName,
            bool useImgui=true
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

#endif
