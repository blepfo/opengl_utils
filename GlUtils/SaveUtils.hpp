#pragma once

/** 
 * Save Png
 */

namespace GlUtils::SaveUtils {

/** 
 * Save from the OpenGL front buffer to PNG
 * Assumes FreeImage has already been initialized
 */
void saveCurrentFrameToPng(const int width, const int height, const char* savePath);

} // namespace GlUtils::SaveUtils
