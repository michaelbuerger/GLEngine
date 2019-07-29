/* TODO: Add ability to load textures from atlas */

/*
 * Image Load Formats (must include stb_image.h if not already included above):
 * STBI_default
 * STBI_rgb
 * STBI_rgb_alpha
 * STBI_grey
 * STBI_grey_alpha
 */

#ifndef GLE_IMAGE_HANDLER_HPP
#define GLE_IMAGE_HANDLER_HPP

#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/graphics/Image.hpp"

#include "stb/stb_image.h"

#include <vector>

namespace GLEngine
{

class ImageHandler
{
public:
    ImageHandler();

    /* Load image data to heap allocated section in memory */
    unsigned char *LoadImageDataFromAddress(const char *address, int *ret_width, int *ret_height, int *ret_colorChannels, const int &imageLoadFormat, const bool &flipVertical);
    /* Free individual image data pointers */
    void FreeImageData(unsigned char *imageData);

    /* Load image data to heap allocated section in memory */
    Image LoadImageFromAddress(const char *address, const int &imageLoadFormat, const bool &flipVertical);
    /* Free individual images */
    void FreeImage(const Image &image);

private:
    std::vector<unsigned char *> loadedImageData; // Not entirely necessary, leaving in for possible later use
};

} // namespace GLEngine

#endif