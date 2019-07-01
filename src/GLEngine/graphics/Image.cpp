#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Image.hpp"

#include "stb/stb_image.h"

#include <iostream>

namespace GLEngine { namespace graphics {

    Image::Image()
    {
        this->loadFormat = -1;
        this->width = -1;
        this->height = -1;
        this->colorChannels = -1;
        this->imageData = nullptr;
    }

    Image::Image(const int& loadFormat, const int& width, const int& height, const int& colorChannels, unsigned char *imageData)
    {
        this->loadFormat = loadFormat;
        this->width = width;
        this->height = height;
        this->colorChannels = colorChannels;
        this->imageData = imageData;
    }

    int Image::GetLoadFormat() const
    {
        return this->loadFormat;
    }
    int Image::GetWidth() const
    {
        return this->width;
    }
    int Image::GetHeight() const
    {
        return this->height;
    }
    int Image::GetColorChannels() const
    {
        return this->colorChannels;
    }
    
    unsigned char* Image::GetImageData() const
    {
        return this->imageData;
    }

    GLuint Image::GetGLFormat() const
    {
        if(this->loadFormat == STBI_rgb_alpha || this->loadFormat == STBI_grey_alpha)
        {
            return GL_RGBA;
        }

        return GL_RGB;
    }
}}