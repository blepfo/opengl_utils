#ifndef _TEXTURE_UTIL_H
#define _TEXTURE_UTIL_H

#include<GL/glew.h>

namespace TextureUtils {

unsigned int textureLoad(
    const char* imagePath,
    GLenum wrap_s = GL_REPEAT,
    GLenum wrap_t = GL_REPEAT,
    GLenum min_filter = GL_NEAREST,
    GLenum mag_filter = GL_NEAREST
);

} // namespace TextureUtils

#endif
