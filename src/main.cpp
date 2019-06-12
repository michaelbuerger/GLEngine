#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

void LoadShaderFromResources(const char* address, const char** sourceReturn) // Note use of const char* for ease of use with string literals
{
    std::string addressResRelative = RESOURCES_PATH;
    addressResRelative.append(address);

    //std::cout << addressResRelative << std::endl;

    std::ifstream file(addressResRelative);
    std::vector<std::string> sourceStr;

    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            sourceStr.push_back(line + "\n");
        }
        file.close();

        //std::cout << "Test" << std::endl;
    } else
    {
        std::cout << "Could not open \"" << addressResRelative << "\"" << std::endl; // Update to use logging
    }

    const char* source[sourceStr.size()];
    for(size_t i=0; i < sourceStr.size(); i++)
    {
        source[i] = sourceStr[i].c_str();
    }

    sourceReturn = source;
}

std::string LoadStringFromResources(const char* address) // Note use of const char* for ease of use with string literals
{
    std::string addressResRelative = RESOURCES_PATH;
    addressResRelative.append(address);

    //std::cout << addressResRelative << std::endl;

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

        //std::cout << "Test" << std::endl;
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
    std::cout << "Entering loop..." << std::endl;

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

    uint vertexShader;
    uint fragmentShader;

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char** vertexShaderSource = NULL;
    const char** fragmentShaderSource = NULL;

    LoadShaderFromResources("shaders/vert1.glsl", vertexShaderSource);
    LoadShaderFromResources("shaders/frag1.glsl", fragmentShaderSource);

    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
    glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

    int success;
    char infoLog[512];

    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << "Vertex Shader Compilation Failed:\n" << infoLog << std::endl;
      return -1;
    }

    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
      glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
      std::cout << "Fragment Shader Compilation Failed:\n" << infoLog << std::endl;
      return -1;
    }

    uint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindAttribLocation(shaderProgram, 0, "pos"); // Note to do this before linking the program

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "Shader Program Linking Failed\n" << infoLog << std::endl;
      return -1;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    /* Loop */
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
