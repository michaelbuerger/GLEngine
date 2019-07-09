/* TODO:
 * Model loading
 * Basic lighting
 * GLFW input handling and such
 TODO:
 * Get rid of methods that load from resources specifically, create method to make address resource relative
 * Add default constructors to every class
 * Add proper checks in ImageHandler
 * Add engine logging to any place that couts currently
 * Remove this-> from all classes before everything except member functions
 * Add m_ before each private variable
 * Convert use of STBI_enums to graphics.hpp or defined.hpp preprocessor defined constants (i.e. GLE_RGB)
 * Issue with free image segfault
 * Figure out segfault on exit
 */

#include "GLEngine/graphics/graphics.hpp"

#define RESOURCES_PATH "/home/michaelbuerger/Documents/Programming Projects/GLEngine/resources/"
#include "GLEngine/defines.hpp"
#include "GLEngine/logging/logging.hpp"
#include "GLEngine/graphics/WindowHandler.hpp"
#include "GLEngine/graphics/Renderer.hpp"
#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/exceptions.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "stb/stb_image.h"

using namespace GLEngine;
using namespace logging;
using namespace graphics;

/* Useful Links:
http://www.opengl-tutorial.org/
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-9-vbo-indexing/
http://www.khronos.org/
http://www.learnopengl.com/
http://www.glfw.org/
https://www.glfw.org/docs/3.0/window.html
https://github.com/nothings/single_file_libs
https://github.com/nothings/stb
https://stackoverflow.com/questions/23150123/loading-png-with-stb-image-for-opengl-texture-gives-wrong-colors
@TODO: Watch this:
 https://www.youtube.com/watch?v=16w9RjrSdBg
*/

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
std::string GetShaderTypeName(const GLuint& shaderType)
{
    switch(shaderType)
    {
        case GL_VERTEX_SHADER: return "GL_VERTEX_SHADER";

        case GL_FRAGMENT_SHADER: return "GL_FRAGMENT_SHADER";
    }

    return "UNKNOWN_SHADER_TYPE";
}

/* Create shader from pre-loaded source */
GLuint CreateShader(const GLchar** shaderSource, const GLuint& shaderType)
{
    GLuint shader;

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
      return -1;
    }

    return shader;
}

/* Create shader from file anywhere in the filesystem */
GLuint CreateShaderFromAddress(const char* address, const GLuint& shaderType)
{
    std::ifstream file(address);

    if(file.is_open() == false)
    {
        std::cout << "Could not open shader at \"" << address << "\"" << std::endl;
        return -1; // TODO: Update to use logging
    }

    unsigned long len = GetFileLength(file);

    if(len == 0)
    {
        std::cout << "Shader is empty at \"" << address << "\"" << std::endl;
        return -1; // TODO: Update to use logging
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
GLuint CreateShaderFromResources(const char* address, const GLuint& shaderType)
{
    std::string resAddress = RESOURCES_PATH;
    resAddress.append(address);
    return CreateShaderFromAddress(resAddress.c_str(), shaderType);
}

/* Creates a shader program with the option to bind attribute locations */ // Look into adding other shader type support
GLuint CreateShaderProgram(const GLuint& vertexShader, const GLuint& fragmentShader, const bool& shouldDeleteShaders, const bool& shouldBindAttribLocations, int* const attribLocations, std::string* const attribNames, const size_t& attribCount)
{
    GLuint shaderProgram = glCreateProgram();

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
GLuint CreateShaderProgram(const GLuint& vertexShader, const GLuint& fragmentShader, const bool& shouldDeleteShaders)
{
    return CreateShaderProgram(vertexShader, fragmentShader, shouldDeleteShaders, false, NULL, NULL, 0);
}

GLuint CreateShaderProgramFromAddresses(const char* vertexShaderAddress, const char* fragmentShaderAddress)
{
    GLuint vertexShader = CreateShaderFromAddress(vertexShaderAddress, GL_VERTEX_SHADER);
    GLuint fragmentShader = CreateShaderFromAddress(fragmentShaderAddress, GL_FRAGMENT_SHADER);

    return CreateShaderProgram(vertexShader, fragmentShader, true);
}

GLuint CreateShaderProgramFromResources(const char* vertexShaderAddress, const char* fragmentShaderAddress)
{
    GLuint vertexShader = CreateShaderFromResources(vertexShaderAddress, GL_VERTEX_SHADER);
    GLuint fragmentShader = CreateShaderFromResources(fragmentShaderAddress, GL_FRAGMENT_SHADER);

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
    WindowHandler windowHandler = WindowHandler();
    // WindowHandler windowHandler(); <-- does not call default constructor for some reason

    GLFWwindow* window;

    std::vector<int> windowHintNames = std::vector<int>();
    std::vector<int> windowHintValues = std::vector<int>();

    windowHintNames.push_back(GLFW_RESIZABLE);
    windowHintValues.push_back(GL_FALSE);

    windowHintNames.push_back(GLFW_CONTEXT_VERSION_MAJOR);
    windowHintValues.push_back(GLE_OPENGL_VERSION_MAJOR);

    windowHintNames.push_back(GLFW_CONTEXT_VERSION_MINOR);
    windowHintValues.push_back(GLE_OPENGL_VERSION_MINOR);

    window = windowHandler.CreateWindow(1280, 720, "GLEngine Test Window 1", NULL, NULL, windowHintNames, windowHintValues);

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

    GLfloat square_vertices_texcoords[]
    {
        1.0f, 1.0f, 0.0f,    1.0f, 1.0f, // top-right
        1.0f, -1.0f, 0.0f,   1.0f, 0.0f, // bottom-right
        -1.0f, 1.0f, 0.0f,   0.0f, 1.0f, // top-left
        -1.0f, -1.0f, 0.0f,  0.0f, 0.0f // bottom-left
    };

    GLint square_indices[]
    {
        2, 1, 3, 0, 1, 2
    };

    GLfloat cube_vertices[] =
    {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);

    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(square_vertices_texcoords), square_vertices_texcoords, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_indices), square_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    Texture testTexture;
    try {
        testTexture = Texture("textures/test-texture.png", STBI_rgb, true);
    } catch (int i)
    {
        switch(i)
        {
            case GLE_IMAGE_DATA_NULL:
                std::cout << "Example catch: Could not load texture" << std::endl;
                exit(-1);
        }
    }

    GLuint shaderProgram = CreateShaderProgramFromResources("shaders/vert1.glsl", "shaders/frag1.glsl");

    glm::vec3 objPosition(0.0f, 0.0f, 0.0f);
    glm::vec3 objScale(1.0f, 1.0f, 1.0f);
    glm::vec3 objRotationEuler(0.0f, 0.0f, 0.0f);

    glm::quat objRotationQuat(objRotationEuler);

    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), objPosition);
    glm::mat4 rotationMatrix = glm::toMat4(objRotationQuat);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), objScale);

    glm::mat4 transformationMatrix = translationMatrix * (rotationMatrix * scaleMatrix);

    //glm::vec3 cameraPosition(2.0f, 1.5f, 1.5f);
    glm::vec3 cameraPosition(0.0f, 0.0f, 1.5f);

    glm::mat4 cameraMatrix = glm::lookAt(cameraPosition, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Look into Unity-style camera handling
    //cameraMatrix = glm::translate(glm::mat4(), cameraPosition);

    glm::mat4 viewMatrix = cameraMatrix;

    float cameraFov = 90.0f;
    float aspectRatio = 16.0f/9.0f;

    glm::mat4 projectionMatrix = glm::perspective(
        glm::radians(cameraFov), // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
        aspectRatio,       // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
        0.1f,              // Near clipping plane. Keep as big as possible, or you'll get precision issues.
        100.0f             // Far clipping plane. Keep as little as possible.
    );

    glm::mat4 mvpMatrix = projectionMatrix * (viewMatrix * transformationMatrix);

    std::cout << "Entering loop..." << std::endl;
    /* Loop */
    while (!windowHandler.ShouldAnyWindowClose())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glCullFace(GL_BACK);
        glUseProgram(shaderProgram);
        testTexture.Bind();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvpMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0, 6*3); // draw without indexing, 6 3D vertices
        glDrawElements(GL_TRIANGLES, sizeof(square_indices)/sizeof(GLuint), GL_UNSIGNED_INT, (void*)0); // draw with indexing

        glfwSwapBuffers(window); // Make sure to update this window variable when changing between windows
        glfwPollEvents();
    }

    windowHandler.~WindowHandler();
    return 0;
}
