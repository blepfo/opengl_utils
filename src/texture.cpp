
#include<stdexcept>

#include<GL/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../include/texture.h"


namespace TextureUtils {

unsigned int textureLoad(
    const char* imagePath,
    GLenum format,
    GLenum wrap_s,
    GLenum wrap_t,
    GLenum min_filter,
    GLenum mag_filter
) {
    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    // Wrapping params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
    // Filtering params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    // Load image
    int width;
    int height;
    int nChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* textureData = stbi_load(imagePath, &width, &height, &nChannels, 0);
    if (!textureData) {
        throw std::runtime_error("Unable to load texture data");
    }
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        format,
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        textureData
    );
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(textureData);
    return textureId;
}


} // namespace TextureUtils
