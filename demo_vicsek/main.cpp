#include <iostream>
#include <sstream>
#include <string>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <FreeImage.h>

// https://github.com/blepfo/opengl_utils
#include "GlUtils/SaveUtils.hpp"
#include "GlUtils/Shader.hpp"
#include "GlUtils/TwoTrianglesRenderer.hpp"


class VicsekRenderer : public GlUtils::TwoTrianglesRenderer {
    public: 
        void setUniforms() override;
        void onRenderLoopLoopback() override;

        VicsekRenderer(
            const char* fragmentShaderPath,
            int screenWidth, 
            int screenHeight, 
            const char* windowName
        ) : GlUtils::TwoTrianglesRenderer(
            fragmentShaderPath, 
            screenWidth, 
            screenHeight, 
            windowName, 
            false
        ) {}

    protected:
        float elapsedTime = 0;
};


void VicsekRenderer::setUniforms() {
    // setUniforms called every render loop iteration
    // SimpleRenderer#run() updates this->deltaTime using glfwGetTime()
    this->elapsedTime += this->deltaTime;
    this->shader->setFloat("iTime", this->elapsedTime);
    this->shader->setVec2("iResolution", glm::vec2(this->screenWidth, this->screenHeight));
}


// Screenshot saving in on
void VicsekRenderer::onRenderLoopLoopback() {
    if (glfwGetKey(this->_window, GLFW_KEY_S) == GLFW_PRESS)  {
        std::stringstream fileNameStream;
        fileNameStream << "./test_" << this->elapsedTime << ".png";
        std::string fileName = fileNameStream.str();

        std::cout << "ATTEMPT TO SAVE TO " << fileName << std::endl;
        GlUtils::SaveUtils::saveCurrentFrameToPng(this->screenWidth, this->screenHeight, fileName.c_str());
    }
}


int main() {
    FreeImage_Initialise();
    // Fragment shader stored in same dir as this file
    const std::string srcPath = __FILE__;
    const std::string dirPath = srcPath.substr(0, srcPath.rfind("/"));
    const std::string fragmentShaderPath = dirPath + "/" + "vicsek.fs";

    VicsekRenderer renderer = VicsekRenderer(fragmentShaderPath.c_str(), 800, 600, "window");
    std::cout << "main - Call renderer.run()" << std::endl;
    FreeImage_DeInitialise();
    return renderer.run();
}
