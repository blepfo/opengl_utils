#include<sstream>

#include<GL/glew.h>
#include<GLFW/glfw3.h>

namespace Init {

GLFWwindow* basicWindow(
    int major, 
    int minor, 
    int width,
    int height,
    const char* name,
    bool mac = true
) {
    bool initialized = glfwInit();
    if (initialized != GL_TRUE) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if (mac) {
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
    // Create window
    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    return window;
}

void glew() {
    glewExperimental = GL_TRUE;
    GLenum initialized = glewInit();
    if (initialized != GLEW_OK) {
        glfwTerminate();
        std::stringstream errorStream;
        errorStream << "Failed to initialize GLEW: " << glewGetErrorString(initialized) << std::endl;
        throw std::runtime_error(errorStream.str());
    }
}

} // namespace Init
