#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>

#include <GL/glew.h>

#include <FreeImage.h>


namespace GlUtils::SaveUtils {

void saveCurrentFrameToPng(
    const int width,
    const int height, 
    const char* savePath
) {
    const int nChannels = 4;
    const int pixelDataSize = width * height * nChannels;
    // Allocate pixelData on in the heap to avoid segfault from giant arr
    // unique_ptr automatically deletes on function exit
    std::unique_ptr<unsigned char[]> pixelData(new unsigned char[pixelDataSize]);
    // Read RGB from the OpenGL front buffer
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixelData.get());

    // Use FreeImage to save PNG
    // 24 bits per pixel = 8 bits * 3 channels
    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);
    if (!bitmap) {
        throw std::runtime_error("GlUtils::SaveUtils::saveCurrentFrameToPng - Failed to allocate FIBITMAP");
    }
    RGBQUAD color;
    for (int i = 0; i < pixelDataSize; i += nChannels) {
        int rowNum = std::floor(i / (nChannels * width));
        int colNum = (i % (nChannels * width)) / nChannels;
        color.rgbRed = pixelData[i];
        color.rgbGreen = pixelData[i + 1];
        color.rgbBlue = pixelData[i + 2];
        // TODO - maybe need to flip vertically
        FreeImage_SetPixelColor(bitmap, colNum, rowNum, &color);
    }

    if (FreeImage_Save(FIF_PNG, bitmap, savePath, 0)) {
        std::cout << "GlUtils::SaveUtils::saveCurrentFrameToPng success to " << savePath << std::endl;
    }
}

} // namespace SaveUtils
