#include<stdexcept>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include<imgui/examples/imgui_impl_opengl3.h>
#include<imgui/examples/imgui_impl_glfw.h>

#include "GlUtils/SimpleRenderer.hpp"
#include "GlUtils/Init.hpp"

namespace GlUtils {


/** 
 * On window resize, update instance variables
 * TODO - find a better way to do this than global variables
 */
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
void resizeCallback(GLFWwindow* window, const int width, const int height) {
    glViewport(0, 0, width, height);
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
}

/**
 *
 */
GlUtils::SimpleRenderer::SimpleRenderer(
    const int screenWidth, 
    const int screenHeight, 
    const char* windowName,
    const bool useImgui
): screenWidth(screenWidth), 
    screenHeight(screenHeight), 
    windowName(windowName),
    useImgui(useImgui) 
{
    SCREEN_WIDTH = screenWidth;
    SCREEN_HEIGHT = screenHeight;
    std::cout 
        << "GlUtils::SimpleRenderer::Init with size (" 
        << this->screenWidth 
        << ", " 
        << this->screenHeight
        << ")"
        << std::endl;
}

/** 
 * Default loop begin - Clear color + depth buffer
 */
void SimpleRenderer::onRenderLoopBegin() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Default loopback - swap buffers and poll events
 */
void SimpleRenderer::onRenderLoopLoopback() {
    glfwSwapBuffers(this->_window);
    glfwPollEvents();
}

/** 
 * Default render gui
 */
void SimpleRenderer::renderGui() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

/** 
 * Delet stuff
 */
void SimpleRenderer::shutdown() {
    glfwTerminate();
    if (this->useImgui) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }
}

int SimpleRenderer::run() {
    try {
        GLFWwindow* window = Init::basicWindow(3, 3, this->screenWidth, this->screenHeight, this->windowName);
        glfwMakeContextCurrent(window);
        ::GlUtils::Init::glew();
        // Framebuffer size callback
        glfwSetFramebufferSizeCallback(window, resizeCallback);
        glEnable(GL_DEPTH_TEST);
        // Imgui
        if (this->useImgui) {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            // TODO - what is io used for
            //ImGuiIO &io = ImGui::GetIO();
            ImGui_ImplGlfw_InitForOpenGL(window, true);
            ImGui_ImplOpenGL3_Init("#version 330 core");
            ImGui::StyleColorsDark();
        }
        this->_window = window;

        this->initScene();

        std::cout << "SimpleRenderer::run() begin render loop" << std::endl;
        float lastFrameTime = 0.0f;
        while (!glfwWindowShouldClose(window)) {
            float currentTime = glfwGetTime();
            this->deltaTime = currentTime - lastFrameTime;
            lastFrameTime = currentTime;

            this->onRenderLoopBegin();

            this->screenWidth = SCREEN_WIDTH;
            this->screenHeight = SCREEN_HEIGHT;

            // Update based on inputs + ImGui changes
            this->processInputs();
            if (this->useImgui) {
                this->createGui();
            }

            this->renderObjects();

            if (this->useImgui) {
                this->renderGui();
            };
            this->onRenderLoopLoopback();

        }
    } catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
        this->shutdown();
        return -1;
    }
    this->shutdown();
    return 0;
}

} // namespace GlUtils
