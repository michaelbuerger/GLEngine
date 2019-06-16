#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define RESOURCES_PATH "/home/michaelbuerger/Documents/Programming/GLEngine/resources/"
#include "GLEngine/defines.hpp"
#include "GLEngine/math/math.hpp"
#include "GLEngine/logging/logging.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace GLEngine;
using namespace logging;
using namespace math;

unsigned long GetFileLength(std::ifstream& file)
{
    if(file.good() == false)
    {
        return 0;
    }
    
    unsigned long pos = file.tellg();
    file.seekg(0, std::ios::end);
    unsigned long len = file.tellg();
    file.seekg(pos);
    
    return len;
}

/* Convert name of shader types based on their id, useful for debugging */ // Add support for other types of shaders
std::string GetShaderTypeName(const uint& shaderType)
{
    switch(shaderType)
    {
        case GL_VERTEX_SHADER:
            return "GL_VERTEX_SHADER";
        break;

        case GL_FRAGMENT_SHADER:
            return "GL_FRAGMENT_SHADER";
        break;
    }

    return "UNKNOWN_SHADER_TYPE";
}

/* Create shader from pre-loaded source */
uint CreateShader(const GLchar** shaderSource, const uint& shaderType)
{
    uint shader;

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, shaderSource, NULL);

    int success;
    char infoLog[512];

    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "Shader Compilation Failed (" << GetShaderTypeName(shaderType) << "):\n" << infoLog << std::endl;
      return 0;
    }

    return shader;
}

/* Create shader from file anywhere in the filesystem */
uint CreateShaderFromAddress(const char* address, const uint& shaderType)
{
    std::ifstream file(address);

    if(file.is_open() == false)
    {
        std::cout << "Could not open shader at \"" << address << "\"" << std::endl;
        return 0; // TODO: Update to use logging
    }

    unsigned long len = GetFileLength(file);

    if(len == 0)
    {
        std::cout << "Shader is empty at \"" << address << "\"" << std::endl;
        return 0; // TODO: Update to use logging
    }

    GLchar shaderSource[len+1];
    shaderSource[len] = 0;

    size_t i=0;
    while (file.good())
    {
        shaderSource[i] = file.get();
        
        if (!file.eof())
        {
            i++;
        }
    }
    
    shaderSource[i] = 0;  // zero terminate

    file.close();

    const GLchar* shaderSourcePointer = shaderSource;

    return CreateShader(&shaderSourcePointer, shaderType);
}

/* Create shader from file in resources */
uint CreateShaderFromResources(const char* address, const uint& shaderType)
{
    std::string resAddress = RESOURCES_PATH;
    resAddress.append(address);
    return CreateShaderFromAddress(resAddress.c_str(), shaderType);
}

/* Creates a shader program with the option to bind attribute locations */ // Look into adding other shader type support
uint CreateShaderProgram(const uint& vertexShader, const uint& fragmentShader, const bool& shouldDeleteShaders, const bool& shouldBindAttribLocations, int* const attribLocations, std::string* const attribNames, const size_t& attribCount)
{
    uint shaderProgram = glCreateProgram();

    int success;
    char infoLog[512];

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    if(shouldBindAttribLocations)
    {
        for(size_t i=0; i<attribCount; i++)
        {
            glBindAttribLocation(shaderProgram, attribLocations[i], attribNames[i].c_str()); // Do this within shader
        }
    }

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "Shader Program Linking Failed\n" << infoLog << std::endl;
      return 0;
    }

    if(shouldDeleteShaders)
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    return shaderProgram;
}

/* Create a shader program without binding attribute locations, assuming the use of layout keyword in shaders themselves */
uint CreateShaderProgram(const uint& vertexShader, const uint& fragmentShader, const bool& shouldDeleteShaders)
{
    return CreateShaderProgram(vertexShader, fragmentShader, shouldDeleteShaders, false, NULL, NULL, 0);
}

uint CreateShaderProgramFromAddresses(const char* vertexShaderAddress, const char* fragmentShaderAddress)
{
    uint vertexShader = CreateShaderFromAddress(vertexShaderAddress, GL_VERTEX_SHADER);
    uint fragmentShader = CreateShaderFromAddress(fragmentShaderAddress, GL_FRAGMENT_SHADER);

    return CreateShaderProgram(vertexShader, fragmentShader, true);
}

uint CreateShaderProgramFromResources(const char* vertexShaderAddress, const char* fragmentShaderAddress)
{
    uint vertexShader = CreateShaderFromResources(vertexShaderAddress, GL_VERTEX_SHADER);
    uint fragmentShader = CreateShaderFromResources(fragmentShaderAddress, GL_FRAGMENT_SHADER);

    return CreateShaderProgram(vertexShader, fragmentShader, true);
}

std::string LoadStringFromResources(const char* address) // Note use of const char* for ease of use with string literals
{
    std::string addressResRelative = RESOURCES_PATH;
    addressResRelative.append(address);

    std::ifstream file(addressResRelative);
    std::string finalString;

    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            finalString.append(line + '\n');
        }
        file.close();
    } else
    {
        std::cout << "Could not open \"" << addressResRelative << "\"" << std::endl;
        return NULL; // TODO: Update to use logging
    }

    return finalString;
}

std::string LoadStringFromAnywhere(const char* address) // Note use of const char* for ease of use with string literals
{
    std::ifstream file(address);
    std::string finalString;

    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            finalString.append(line + '\n');
        }
        file.close();
    } else
    {
        std::cout << "Could not open \"" << address << "\"" << std::endl;
        return NULL; // TODO: Update to use logging
    }

    return finalString;
}

int main(void)
{
    /* Initialize GLFW and create window */
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLE_OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLE_OPENGL_VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(1280, 720, "GLFW Example Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    }

    /* Print useful information */
    std::cout << "Latest supported OpenGL version on this system is " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEngine is currently using OpenGL version " << GLE_OPENGL_VERSION_MAJOR << "." << GLE_OPENGL_VERSION_MINOR << std::endl;

    float triangle_vertices[] = { // Triangle declared in 3D space
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    uint VBO;
    glGenBuffers(1, &VBO);

    uint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
    glEnableVertexAttribArray(0); 

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Example of unbinding buffer

    uint shaderProgram = CreateShaderProgramFromResources("shaders/vert1.glsl", "shaders/frag1.glsl");

    std::cout << "Entering loop..." << std::endl;

    /* Loop */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
