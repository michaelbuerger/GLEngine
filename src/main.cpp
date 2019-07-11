/* TODO:
 * Model loading
 * Move IO functions that are independent of shader stuff to own header and cpp file
 * Move shader code to Shader class
 * Basic lighting
 * GLFW input handling and such
 * Convert to using unique_ptr, shared_ptr, and weak_ptr when possible
 * TODO:
 * Get rid of methods that load from resources specifically, create method to make address resource relative
 * Look into returning image data from image data load methods in image handler to return by ref
 * Add default constructors to every class
 * Add proper checks in ImageHandler
 * Add engine logging to any place that couts currently
 * Remove this-> from all classes before everything except member functions
 * Add m_ before each private variable
 * Convert use of STBI_enums to graphics.hpp or defined.hpp preprocessor defined constants (i.e. GLE_RGB)
 * Issue with free image segfault
 * Figure out segfault on exit
 * Index generator for varying combinations of vertices, texcoords, and normals
 */

#include "GLEngine/graphics/graphics.hpp"

#define RESOURCES_PATH "/home/michaelbuerger/Documents/Programming Projects/GLEngine/resources/"
#include "GLEngine/defines.hpp"
#include "GLEngine/logging/logging.hpp"
#include "GLEngine/io/io.hpp"
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
using namespace io;

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
https://mbevin.wordpress.com/2012/11/18/smart-pointers/
@TODO: Watch this:
 https://www.youtube.com/watch?v=16w9RjrSdBg
*/

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
    try { // TODO: Add try catch statement within constructors of Texture, plus engine logging
        testTexture = Texture("textures/test-texture.png", STBI_rgb, true);
    } catch (GLE_IMAGE_DATA_NULL& e)
    {
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    GLuint shaderProgram = CreateShaderProgramFromAddresses(ResPathRelative("shaders/vert1.glsl").c_str(), ResPathRelative("shaders/frag1.glsl").c_str());

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

    glfwMakeContextCurrent(window); // Note: Only have to call this before rendering
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
