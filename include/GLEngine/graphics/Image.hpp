#ifndef GLE_IMAGE_HPP
#define GLE_IMAGE_HPP

#include "GLEngine/graphics/graphics.hpp"

namespace GLEngine
{

class Image
{
public:
    Image();
    /* NOTE: This assumes that image data is properly loaded by stbi_image, no checks are performed */
    Image(const int &loadFormat, const int &width, const int &height, const int &colorChannels, unsigned char *imageData);
    /* Note that right now, flipVertical is only an option when loading image from file */
    Image(const char *address, const int &loadFormat, const bool &flipVertical);

    int GetLoadFormat() const;
    int GetWidth() const;
    int GetHeight() const;
    int GetColorChannels() const;
    unsigned char *GetImageData() const;
    GLuint GetGLFormat() const;

    ~Image();

private:
    int m_loadFormat;
    int m_width, m_height, m_colorChannels;

    unsigned char *m_imageData;
};

} // namespace GLEngine

#endif