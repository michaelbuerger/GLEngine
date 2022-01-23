#include "GLEngine/io/io.hpp"

#include "GLEngine/defines.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/exceptions.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace GLEngine
{

std::string ResInfo::resPath = "./resources/";

/*
 * Redefine GLEngine::ResInfo::resPath to edit resources path
 * default <-- resPath = "./resources/"
 */
std::string ResPathRelative(const char *address)
{
    std::string resAddress = ResInfo::resPath;
    resAddress.append(address);

    return resAddress;
}

unsigned long GetFileLength(std::ifstream &file)
{
    if (file.good() == false)
    {
        return 0;
    }

    unsigned long pos = file.tellg();
    file.seekg(0, std::ios::end);
    unsigned long len = file.tellg();
    file.seekg(pos);

    return len;
}

bool CanCharBeStartOfNumber(const char &c)
{
    return (c == '+' || c == '-' || c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9');
}

/* Convert name of shader types based on their id, useful for debugging */ // Add support for other types of shaders
std::string GetShaderTypeName(const GLuint &shaderType)
{
    switch (shaderType)
    {
    case GL_VERTEX_SHADER:
        return "GL_VERTEX_SHADER";

    case GL_FRAGMENT_SHADER:
        return "GL_FRAGMENT_SHADER";
    }

    return "UNKNOWN_SHADER_TYPE";
}

/* Create shader from pre-loaded source */
GLuint CreateShader(const GLchar **shaderSource, const GLuint &shaderType)
{
    GLuint shader;

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, shaderSource, NULL);

    int success;
    char infoLog[512];

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Shader Compilation Failed (" << GetShaderTypeName(shaderType) << "):\n"
                  << infoLog << std::endl;
        return -1;
    }

    return shader;
}

/* Create shader from file anywhere in the filesystem */
GLuint CreateShaderFromAddress(const char *address, const GLuint &shaderType)
{
    std::ifstream file(address);

    if (file.is_open() == false)
    {
        std::cout << "Could not open shader at \"" << address << "\"" << std::endl;
        throw GLE_CANT_OPEN_FILE();
        return -1; // TODO: Update to use logging
    }

    unsigned long len = GetFileLength(file);

    if (len == 0)
    {
        std::cout << "Shader is empty at \"" << address << "\"" << std::endl;
        throw GLE_CANT_OPEN_FILE();
        file.close();
        return -1; // TODO: Update to use logging
    }

    GLchar shaderSource[len + 1];
    shaderSource[len] = 0;

    size_t i = 0;
    while (file.good())
    {
        shaderSource[i] = file.get();

        if (!file.eof())
        {
            i++;
        }
    }

    shaderSource[i] = 0; // zero terminate

    file.close();

    const GLchar *shaderSourcePointer = shaderSource;

    return CreateShader(&shaderSourcePointer, shaderType);
}

/* Creates a shader program with the option to bind attribute locations */ // Look into adding other shader type support
GLuint CreateShaderProgram(const GLuint &vertexShader, const GLuint &fragmentShader, const bool &shouldDeleteShaders, const bool &shouldBindAttribLocations, int *const attribLocations, std::string *const attribNames, const size_t &attribCount)
{
    GLuint shaderProgram = glCreateProgram();

    int success;
    char infoLog[512];

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    if (shouldBindAttribLocations)
    {
        for (size_t i = 0; i < attribCount; i++)
        {
            glBindAttribLocation(shaderProgram, attribLocations[i], attribNames[i].c_str()); // Do this within shader
        }
    }

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Shader Program Linking Failed\n"
                  << infoLog << std::endl;
        return 0;
    }

    if (shouldDeleteShaders)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    return shaderProgram;
}

/* Create a shader program without binding attribute locations, assuming the use of layout keyword in shaders themselves */
GLuint CreateShaderProgram(const GLuint &vertexShader, const GLuint &fragmentShader, const bool &shouldDeleteShaders)
{
    return CreateShaderProgram(vertexShader, fragmentShader, shouldDeleteShaders, false, NULL, NULL, 0);
}

GLuint CreateShaderProgramFromAddresses(const char *vertexShaderAddress, const char *fragmentShaderAddress)
{
    GLuint vertexShader = CreateShaderFromAddress(vertexShaderAddress, GL_VERTEX_SHADER);
    GLuint fragmentShader = CreateShaderFromAddress(fragmentShaderAddress, GL_FRAGMENT_SHADER);

    return CreateShaderProgram(vertexShader, fragmentShader, true);
}

std::string LoadStringFromAddress(const char *address) // Note use of const char* for ease of use with string literals
{
    std::ifstream file(address);
    std::string finalString;

    if (file.is_open())
    {
        std::string line;
        while (getline(file, line))
        {
            finalString.append(line + '\n');
        }
        file.close();
    }
    else
    {
        std::cout << "Could not open \"" << address << "\"" << std::endl;
        return NULL; // TODO: Update to use logging
    }

    return finalString;
}

} // namespace GLEngine