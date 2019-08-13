#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Image.hpp"

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
    m_canBeFreed = false;
}

/* NOTE: This assumes that image data is properly loaded by stbi_image, no checks are performed */
Image::Image(const int &loadFormat, const int &width, const int &height, const int &colorChannels, unsigned char *imageData)
{
    m_loadFormat = loadFormat;
    m_width = width;
    m_height = height;
    m_colorChannels = colorChannels;
    m_imageData = imageData;
    m_canBeFreed = true;
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

bool Image::CanBeFreed() const
{
    return m_canBeFreed;
}

void Image::Free()
{
    if (m_canBeFreed)
    {
        stbi_image_free(m_imageData);
    }
}

Image::~Image()
{
    this->Free();
}

} // namespace GLEngine