#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/io/io.hpp"
#include "GLEngine/logging/Log.hpp"

#include <cmath>
#include <vector>
#include <iostream>
#include <memory>

namespace GLEngine
{

/* Load texture from resources */
Texture::Texture(const char *address, const int &loadFormat, const bool &shouldGenerateMipmaps)
{
    this->image = std::make_shared<Image>(address, loadFormat, true);
    this->GenTextureID();
    this->Create(shouldGenerateMipmaps);
    m_texParamNames = std::vector<GLuint>();
    m_texParamValues = std::vector<GLuint>();
}
Texture::Texture(const Texture &texture)
{
    this->image = texture.image;
    m_textureID = texture.GetGLID();
    m_texParamNames = std::vector<GLuint>();
    m_texParamValues = std::vector<GLuint>();
}

/* Creates texture from previously loaded image data */
Texture::Texture(Image &image, const bool &shouldGenerateMipmaps)
{
    this->image = std::make_shared<Image>(image);
    this->GenTextureID();
    this->Create(shouldGenerateMipmaps);
    m_texParamNames = std::vector<GLuint>();
    m_texParamValues = std::vector<GLuint>();
}

/* Texture bind will only override another if it is on the same texture slot */
void Texture::Bind(const GLuint& textureSlot) const
{
    glActiveTexture(textureSlot);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
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
    return m_textureID;
}

void Texture::GenTextureID()
{
    glGenTextures(1, &m_textureID);
    if (m_textureID == 0)
    {
        GLE_ENGINE_ERROR("{}", "\"In method Texture::GenTextureID.\". Failed to generate texture ID.");
        // Update to handle other possible errors (request error log from OpenGL)
    }
}

void Texture::Create(const bool &shouldGenerateMipmaps)
{
    if (m_textureID != 0)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureID);
        for (size_t i = 0; i < std::min(m_texParamNames.size(), m_texParamValues.size()); i++)
        {
            glTexParameteri(GL_TEXTURE_2D, m_texParamNames[i], m_texParamValues[i]);
        }
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, this->image->GetGLFormat(), this->image->GetWidth(), this->image->GetHeight(), 0, this->image->GetGLFormat(), GL_UNSIGNED_BYTE, this->image->GetImageData());
        if (shouldGenerateMipmaps)
        {
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
    else
    {
        GLE_ENGINE_ERROR("{}", "In method \"Texture::Create\". Failed to create texture, m_textureID == 0.");
    }
}

} // namespace GLEngine