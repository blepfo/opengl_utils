#ifndef _INIT_UTIL_H
#define _INIT_UTIL_H

#include<GLFW/glfw3.h>

namespace Init {

GLFWwindow* basicWindow(
    int major, 
    int minor,
    int width,
    int height, 
    const char* name,
    bool mac = true
);

void glew();
    

} // Init namespace

#endif
