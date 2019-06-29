#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "GLEngine/graphics/graphics.hpp"

namespace GLEngine { namespace graphics {

    class Image 
    {
        public:
            Image();
            Image(const int& loadFormat, const int& width, const int& height, const int& colorChannels, unsigned char *imageData);

            int GetLoadFormat() const;
            int GetWidth() const;
            int GetHeight() const;
            int GetColorChannels() const;
            unsigned char* GetImageData() const;
            GLuint GetGLFormat() const;

        private:
            int loadFormat;
            int width, height, colorChannels;

            unsigned char* imageData;
    };

}}

#endif