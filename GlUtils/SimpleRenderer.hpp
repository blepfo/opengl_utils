#pragma once

#include<unordered_map>
#include<string>
#include<iostream>

namespace GlUtils {

class SimpleRenderer {
    public:
        SimpleRenderer(
            const int screenWidth, 
            const int screenHeight, 
            const char* windowName,
            const bool useImgui = true
        );
        // Initialize objects in the scene
        virtual void initScene() = 0;
        // For each object, bind its VAO, activate shaders, assign uniforms
        virtual void renderObjects() = 0;
        // Handle user input and update instance variables
        virtual void processInputs() {};
        // Create ImGui, updating instance variables 
        virtual void createGui() {};

        virtual void onRenderLoopBegin();
        virtual void onRenderLoopLoopback();
        virtual void renderGui();
        void shutdown();

        int run();

        int deltaTime;

    protected:
        int screenWidth;
        int screenHeight;
        bool useImgui;
        const char* windowName;

        GLFWwindow* _window;
};

} // namespace GlUtils
