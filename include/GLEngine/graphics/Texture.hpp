#ifndef GLE_TEXTURE_HPP
#define GLE_TEXTURE_HPP

#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/ImageHandler.hpp"
#include "GLEngine/graphics/Image.hpp"

#include <vector>

namespace GLEngine
{

/* Non-PNG will work, but if the format doesn't support alpha channels they will not be generated */
class Texture
{
public:
    static class ImageHandler imageHandler;

    Texture();
    /* Load texture from resources */
    Texture(const char *address, const int &loadFormat, const bool &shouldGenerateMipmaps);
    Texture(const Texture &texture);

    /* Creates texture from previously loaded image */
    Texture(const Image &image, const bool &shouldGenerateMipmaps);

    void Bind() const;
    void Unbind() const;

    /* TODO: Figure out if glTexImage2D actually needs to be recalled when changing params */

    /* Binds texID, sets parameters to default (see definition), must recall Create(), unbinds texID */
    void SetDefaultParameters();
    /* Binds texID, sets integer parameters based on below names and values, must recall Create(), unbinds texID */
    void SetIntParameters(const std::vector<GLuint> &texParamNames, const std::vector<GLuint> &texParamValues);

    Image GetImage() const;
    /* Get OpenGL texture ID */
    GLuint GetGLID() const;

    ~Texture();

    Image image;

private:
    //Image image;
    GLuint textureID;

    void GenTextureID();
    void Create(const bool &shouldGenerateMipmaps);

    std::vector<GLuint> m_texParamNames;
    std::vector<GLuint> m_texParamValues;
};

} // namespace GLEngine

#endif