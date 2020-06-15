#pragma once

#include<GL/glew.h>


namespace GlUtils::TextureUtils {

unsigned int textureLoad(
    const char* imagePath,
    const GLenum wrap_s = GL_REPEAT,
    const GLenum wrap_t = GL_REPEAT,
    const GLenum min_filter = GL_NEAREST,
    const GLenum mag_filter = GL_NEAREST
);

} // namespace GlUtils::TextureUtils
