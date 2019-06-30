#include "GLEngine/graphics/ImageHandler.hpp"
#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/graphics/Image.hpp"
#include "GLEngine/defines.hpp"
#include "GLEngine/exceptions.hpp"

#include "stb/stb_image.h"

#include <vector>
#include <string>
#include <iostream>

namespace GLEngine { namespace graphics {

    ImageHandler::ImageHandler()
    {
        loadedImageData = std::vector<unsigned char*>();
    }

    /* Load image file of given width, height, and channels to heap allocated section in memory */
    unsigned char *ImageHandler::LoadImageDataFromFile(const char *address, int *ret_width, int *ret_height, int *ret_colorChannels, const int& imageLoadFormat)
    {
        unsigned char* imageData = stbi_load(address, ret_width, ret_height, ret_colorChannels, imageLoadFormat);
        if(imageData != NULL)
        {
            this->loadedImageData.push_back(imageData);
        }

        return imageData;
    }

    /* Load image file of given width, height, and channels to heap allocated section in memory (from resources path) */
    unsigned char *ImageHandler::LoadImageDataFromResources(const char *address, int *ret_width, int *ret_height, int *ret_colorChannels, const int& imageLoadFormat)
    {
        std::string resAddress = RESOURCES_PATH;
        resAddress.append(address);

        return this->LoadImageDataFromFile(resAddress.c_str(), ret_width, ret_height, ret_colorChannels, imageLoadFormat);
    }

    /* Free individual images */
    void ImageHandler::FreeImageData(unsigned char *imageData)
    {
        stbi_image_free(imageData); // Free image data
        for(size_t i=0; i<this->loadedImageData.size(); i++) // Try to find in loaded image data vector, if found remove it
        {
            if(imageData == this->loadedImageData.at(i))
            {
                this->loadedImageData.erase(this->loadedImageData.begin()+i);
            }
        }
    }

    /* Load image data to heap allocated section in memory */
    Image ImageHandler::LoadImageFromFile(const char *address, const int& imageLoadFormat)
    {
        int colorChannels, width, height;
        unsigned char* imageData = LoadImageDataFromFile(address, &width, &height, &colorChannels, imageLoadFormat);

        if(imageData == NULL)
        {
            std::cout << "Loaded image data from \"" << address << "\"is null..." << std::endl;
            std::cout << "...stbi failure reason is:" << stbi_failure_reason() << std::endl; // Update to use logging
            throw GLE_IMAGE_DATA_NULL; // main cause is failing to find file or not having permission to open (can't fopen)
        }

        Image image = Image(imageLoadFormat, width, height, colorChannels, imageData);

        return image;
    }
    /* Load image data to heap allocated section in memory (from resources path) */
    Image ImageHandler::LoadImageFromResources(const char *address, const int& imageLoadFormat)
    {
        int colorChannels, width, height;
        unsigned char* imageData = LoadImageDataFromResources(address, &width, &height, &colorChannels, imageLoadFormat);

        if(imageData == NULL)
        {
            std::cout << "Loaded image data from \"" << address << "\"is null..." << std::endl;
            std::cout << "...stbi failure reason is:" << stbi_failure_reason() << std::endl; // Update to use logging
            throw GLE_IMAGE_DATA_NULL; // main cause is failing to find file or not having permission to open (can't fopen)
        }

        Image image = Image(imageLoadFormat, width, height, colorChannels, imageData);

        return image;
    }
    /* Free individual image data pointers */
    void ImageHandler::FreeImage(const Image& image)
    {
        this->FreeImageData(image.GetImageData());
    }

    /* Free all heap allocated sections */
    ImageHandler::~ImageHandler()
    {
        for(size_t i=0; i<this->loadedImageData.size(); i++)
        {
            stbi_image_free(this->loadedImageData.at(i));
        }
    }
}}