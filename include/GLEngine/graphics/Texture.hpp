#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "GLEngine/graphics/ImageHandler.hpp"
#include "GLEngine/graphics/Image.hpp"

namespace GLEngine { namespace graphics {

    /* Non-PNG will work, but if the format doesn't support alpha channels they will not be generated */
    class Texture
    {
        public:
            static class ImageHandler imageHandler;

            Texture();
            /* Load texture from resources */
            Texture(const char* address, const int& loadFormat);
            Texture(const Texture& texture);

            /* Creates texture from previously loaded image */
            Texture(const Image& image);
            ~Texture();

            Image GetImage() const;

        private:
            Image image;
    };

}}

#endif