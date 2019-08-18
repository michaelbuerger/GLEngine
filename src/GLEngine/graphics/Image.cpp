#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Image.hpp"
#include "GLEngine/logging/Log.hpp"
#include "GLEngine/exceptions.hpp"

#include "stb/stb_image.h"

#include <iostream>

namespace GLEngine
{

Image::Image()
{
    m_loadFormat = -1;
    m_width = -1;
    m_height = -1;
    m_colorChannels = -1;
    m_imageData = nullptr;
}

/* NOTE: This assumes that image data is properly loaded by stbi_image, no checks are performed */
Image::Image(const int &loadFormat, const int &width, const int &height, const int &colorChannels, unsigned char *imageData)
{
    m_loadFormat = loadFormat;
    m_width = width;
    m_height = height;
    m_colorChannels = colorChannels;
    m_imageData = imageData;
}

/* Note that right now, flipVertical is only an option when loading image from file */
Image::Image(const char *address, const int &loadFormat, const bool &flipVertical)
{
    m_loadFormat = loadFormat;
    m_width = -1;
    m_height = -1;
    m_colorChannels = -1;
    m_imageData = nullptr;

    int colorChannels, width, height;

    stbi_set_flip_vertically_on_load(flipVertical);
    unsigned char *imageData = stbi_load(address, &width, &height, &colorChannels, loadFormat);

    if (imageData == nullptr)
    {
        GLE_ENGINE_ERROR("In method \"Image::Image\":");
        GLE_ENGINE_ERROR("Loaded image data from \"{}\" is null", address);
        GLE_ENGINE_ERROR("stbi failure reason is: {}", stbi_failure_reason());
        throw GLE_IMAGE_DATA_NULL();
    }

    m_width = width;
    m_height = height;
    m_colorChannels = colorChannels;
    m_imageData = imageData;
}

int Image::GetLoadFormat() const
{
    return m_loadFormat;
}
int Image::GetWidth() const
{
    return m_width;
}
int Image::GetHeight() const
{
    return m_height;
}
int Image::GetColorChannels() const
{
    return m_colorChannels;
}

unsigned char *Image::GetImageData() const
{
    return m_imageData;
}

GLuint Image::GetGLFormat() const
{
    if (m_loadFormat == STBI_rgb_alpha || m_loadFormat == STBI_grey_alpha)
    {
        return GL_RGBA;
    }

    return GL_RGB;
}

Image::~Image()
{
    stbi_image_free(this->GetImageData());
}

} // namespace GLEngine