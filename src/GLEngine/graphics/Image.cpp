#include "GLEngine/graphics/Image.hpp"

namespace GLEngine { namespace graphics {

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
}}