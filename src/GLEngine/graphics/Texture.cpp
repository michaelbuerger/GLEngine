#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/graphics/ImageHandler.hpp"
#include "GLEngine/io/io.hpp"

#include <cmath>
#include <vector>
#include <iostream>

namespace GLEngine
{

ImageHandler Texture::imageHandler = ImageHandler();

/* Load texture from resources */
Texture::Texture(const char *address, const GLuint &textureSlot, const int &loadFormat, const bool &shouldGenerateMipmaps)
{
    this->image = Texture::imageHandler.LoadImageFromAddress(ResPathRelative(address).c_str(), loadFormat, true);
    this->GenTextureID();
    m_textureSlot = textureSlot;
    this->Create(shouldGenerateMipmaps);
    m_texParamNames = std::vector<GLuint>();
    m_texParamValues = std::vector<GLuint>();
}
Texture::Texture(const Texture &texture)
{
    this->image = texture.GetImage();
    this->textureID = texture.GetGLID();
    m_textureSlot = texture.GetTextureSlot();
    m_texParamNames = std::vector<GLuint>();
    m_texParamValues = std::vector<GLuint>();
}

/* Creates texture from previously loaded image data */
Texture::Texture(const Image &image, const GLuint &textureSlot, const bool &shouldGenerateMipmaps)
{
    this->image = image;
    GenTextureID();
    m_textureSlot = textureSlot;
    this->Create(shouldGenerateMipmaps);
    m_texParamNames = std::vector<GLuint>();
    m_texParamValues = std::vector<GLuint>();
}

/* Texture bind will only override another if it is on the same texture slot */
void Texture::Bind() const
{
    glActiveTexture(m_textureSlot);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}
void Texture::Unbind() const
{
    glActiveTexture(m_textureSlot);
    glBindTexture(GL_TEXTURE_2D, 0);
}

/* TODO: Figure out if glTexImage2D actually needs to be recalled when changing params */

/* Binds texID, sets parameters to default (OpenGL default then definition spec default), must recall Create(), unbinds texID */
void Texture::SetDefaultParameters()
{
    m_texParamNames.push_back(GL_TEXTURE_WRAP_S);
    m_texParamValues.push_back(GL_REPEAT);

    m_texParamNames.push_back(GL_TEXTURE_WRAP_T);
    m_texParamValues.push_back(GL_REPEAT);

    m_texParamNames.push_back(GL_TEXTURE_MIN_FILTER);
    m_texParamValues.push_back(GL_LINEAR);

    m_texParamNames.push_back(GL_TEXTURE_MAG_FILTER);
    m_texParamValues.push_back(GL_LINEAR);
}
/* Binds texID, sets integer parameters based on below names and values, must recall Create(), unbinds texID */
void Texture::SetIntParameters(const std::vector<GLuint> &texParamNames, const std::vector<GLuint> &texParamValues)
{
    for (size_t i = 0; i < std::min(texParamNames.size(), texParamValues.size()); i++)
    {
        m_texParamNames.push_back(texParamNames[i]);
        m_texParamValues.push_back(texParamValues[i]);
    }
}

/* Get OpenGL texture ID */
GLuint Texture::GetGLID() const
{
    return this->textureID;
}

Image Texture::GetImage() const
{
    return this->image;
}

GLuint Texture::GetTextureSlot() const
{
    return m_textureSlot;
}

void Texture::GenTextureID()
{
    glGenTextures(1, &this->textureID);
    if (this->textureID == 0)
    {
        std::cout << "Could not generate texture ID" << std::endl;
        // Update to use logging and handle other possible errors (request error log from OpenGL)
    }
}

void Texture::Create(const bool &shouldGenerateMipmaps)
{
    if (this->textureID != 0)
    {
        this->Bind();
        for (size_t i = 0; i < std::min(m_texParamNames.size(), m_texParamValues.size()); i++)
        {
            glTexParameteri(GL_TEXTURE_2D, m_texParamNames[i], m_texParamValues[i]);
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->image.GetWidth(), this->image.GetHeight(), 0, this->image.GetGLFormat(), GL_UNSIGNED_BYTE, this->image.GetImageData());
        if (shouldGenerateMipmaps)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }

        this->Unbind();
    }
    else
    {
        // Add call noting textureID not being generated
    }

    // TODO: Texture::imageHandler.FreeImage(image); This segfaults for some reason
    // Googled cause = trying to free pointer that wasn't allocated with malloc (might even be stack allocated)
    // For now this might cause memory leaks but it is in debug mode so that's not a real issue
    // Look into this
}

Texture::~Texture()
{
    Texture::imageHandler.FreeImage(this->image);
}

} // namespace GLEngine