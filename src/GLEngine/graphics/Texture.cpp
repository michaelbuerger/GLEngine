#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/graphics/ImageHandler.hpp"

namespace GLEngine { namespace graphics {

    /* Load texture from resources */
    Texture::Texture(const char* address, const int& loadFormat)
    {
        this->image = Texture::imageHandler.LoadImageFromResources(address, loadFormat);
    }
    Texture::Texture(const Texture& texture)
    {
        this->image = texture.GetImage();
    }

    /* Creates texture from previously loaded image data */
    Texture::Texture(const Image& image)
    {
        this->image = image;
    }

    Texture::~Texture()
    {
        Texture::imageHandler.FreeImage(this->image);
    }

    Image Texture::GetImage() const
    {
        return this->image;
    }

}}