#pragma once

#include<GLFW/glfw3.h>


namespace GlUtils::Init {

GLFWwindow* basicWindow(
    const int major, 
    const int minor,
    const int width,
    const int height, 
    const char* name,
    const bool mac = true
);

void glew();

} // namespace GlUtils::Init
