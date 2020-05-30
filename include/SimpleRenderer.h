#ifndef _SIMPLE_RENDERER_H
#define _SIMPLE_RENDERER_H

#include<unordered_map>
#include<string>
#include<iostream>

class SimpleRenderer {
    public:
        SimpleRenderer(
            int screenWidth, 
            int screenHeight, 
            const char* windowName,
            bool useImgui = true
        );
        // Initialize objects in the scene
        virtual void initScene() = 0;
        // Handle user input and update instance variables
        virtual void processInputs() = 0;
        // Create ImGui, updating instance variables 
        virtual void createGui() = 0;
        // For each object, bind its VAO, activate shaders, assign uniforms
        virtual void renderObjects() = 0;

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

#endif
