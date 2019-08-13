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

    int GetLoadFormat() const;
    int GetWidth() const;
    int GetHeight() const;
    int GetColorChannels() const;
    unsigned char *GetImageData() const;
    GLuint GetGLFormat() const;

    bool CanBeFreed() const; // returns m_canBeFreed;
    void Free();             // frees image data if canBeFreed == true

    ~Image();

private:
    int m_loadFormat;
    int m_width, m_height, m_colorChannels;

    unsigned char *m_imageData;

    bool m_canBeFreed;
};

} // namespace GLEngine

#endif