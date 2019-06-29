#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/graphics/ImageHandler.hpp"

#include <cmath>
#include <vector>
#include <iostream>

namespace GLEngine { namespace graphics {

    ImageHandler Texture::imageHandler = ImageHandler();

    Texture::Texture()
    {
        this->GenTextureID();
    }

    /* Load texture from resources */
    Texture::Texture(const char* address, const int& loadFormat)
    {
        this->image = Texture::imageHandler.LoadImageFromResources(address, loadFormat);
        this->GenTextureID();
    }
    Texture::Texture(const Texture& texture)
    {
        this->image = texture.GetImage();
        this->textureID = texture.GetGLID();
    }

    /* Creates texture from previously loaded image data */
    Texture::Texture(const Image& image)
    {
        this->image = image;
        GenTextureID();
    }

    void Texture::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, this->textureID);
    }
    void Texture::Unbind() const
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    /* TODO: Figure out if glTexImage2D actually needs to be recalled when changing params */

    /* Binds texID, sets parameters to default (OpenGL default then definition spec default), must recall Create(), unbinds texID */ 
    void Texture::SetDefaultParameters() const
    {
        if(this->textureID != 0)
        {
            this->Bind();
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            this->Unbind();
            return;
        }
        // Add call noting textureID not being generated
    }
    /* Binds texID, sets integer parameters based on below names and values, must recall Create(), unbinds texID */
    void Texture::SetIntParameters(const std::vector<GLuint>& texParamNames, const std::vector<GLuint>& texParamValues) const
    {
        if(this->textureID != 0)
        {
            this->Bind();
            for(size_t i=0; i<std::min(texParamNames.size(), texParamValues.size()); i++)
            {
                glTexParameteri(GL_TEXTURE_2D, texParamNames.at(i), texParamValues.at(i));
            }
            this->Unbind();
            return;
        }
        // Add call noting textureID not being generated
    }

    /* Binds texID, sets integer parameters based on below names and values, must recall Create(), unbinds texID */
    void Texture::SetFloatParameters(const std::vector<GLfloat>& texParamNames, const std::vector<GLfloat>& texParamValues) const
    {
        if(this->textureID != 0)
        {
            this->Bind();
            for(size_t i=0; i<std::min(texParamNames.size(), texParamValues.size()); i++)
            {
                glTexParameterf(GL_TEXTURE_2D, texParamNames.at(i), texParamValues.at(i));
            }
            this->Unbind();
            return;
        }

        // Add call noting textureID not being generated
    }

    void Texture::Create(const bool& shouldGenerateMipmaps)
    {
        if(this->textureID != 0)
        {
            this->Bind();

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->image.GetWidth(), this->image.GetHeight(), 0, this->image.GetGLFormat(), GL_UNSIGNED_BYTE, this->image.GetImageData());
            if(shouldGenerateMipmaps)
            glGenerateMipmap(GL_TEXTURE_2D);

            this->Unbind();
            return;
        }
        // Add call noting textureID not being generated
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

    void Texture::GenTextureID()
    {
        glGenTextures(1, &this->textureID);
        if(this->textureID == 0)
        {
            std::cout << "Could not generate texture ID" << std::endl; 
            // Update to use logging and handle other possible errors (request error log from OpenGL)
        }
    }

    Texture::~Texture()
    {
        Texture::imageHandler.FreeImage(this->image);
    }

}}