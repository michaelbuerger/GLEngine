#ifndef IO_HPP
#define IO_HPP

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace GLEngine { namespace io {

    std::string ResPathRelative(const char* address);

    unsigned long GetFileLength(std::ifstream& file);

    /* Convert name of shader types based on their id, useful for debugging */ // Add support for other types of shaders
    std::string GetShaderTypeName(const GLuint& shaderType);

    /* Create shader from pre-loaded source */
    GLuint CreateShader(const GLchar** shaderSource, const GLuint& shaderType);

    /* Create shader from file anywhere in the filesystem */
    GLuint CreateShaderFromAddress(const char* address, const GLuint& shaderType);

    /* Creates a shader program with the option to bind attribute locations */ // Look into adding other shader type support
    GLuint CreateShaderProgram(const GLuint& vertexShader, const GLuint& fragmentShader, const bool& shouldDeleteShaders, const bool& shouldBindAttribLocations, int* const attribLocations, std::string* const attribNames, const size_t& attribCount);

    /* Create a shader program without binding attribute locations, assuming the use of layout keyword in shaders themselves */
    GLuint CreateShaderProgram(const GLuint& vertexShader, const GLuint& fragmentShader, const bool& shouldDeleteShaders);

    GLuint CreateShaderProgramFromAddresses(const char* vertexShaderAddress, const char* fragmentShaderAddress);

    std::string LoadStringFromAddress(const char* address); // Note use of const char* for ease of use with string literals

}}

#endif