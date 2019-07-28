/* TODO:
 * Fix model loading
 * Move shader code to Shader class
 * Basic lighting
 * GLFW input handling and such
 * Convert to using unique_ptr, shared_ptr, and weak_ptr when possible
 * TODO:
 * Get rid of methods that load from resources specifically, create method to make address resource relative
 * Add default constructors to every class
 * Add proper checks in ImageHandler
 * Add engine logging to any place that couts currently
 * Remove this-> from all classes before everything except member functions
 * Add m_ before each private variable
 * Convert use of STBI_enums to graphics.hpp or defined.hpp preprocessor defined constants (i.e. GLE_RGB)
 * Issue with free image segfault
 * Figure out segfault on exit (segfault now gone, convert to using unique_ptr, shared_ptr, weak_ptr in ImageHandler)
 * Get rid of WindowHandler's manual destruction of windows, make Window class that has its own destructor, have WindowHandler create shared ptr to Window classes
 * http://www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
 */

#include "GLEngine/graphics/graphics.hpp"

#define RESOURCES_PATH "/home/michaelbuerger/Documents/Programming Projects/GLEngine/resources/"
#include "GLEngine/defines.hpp"
#include "GLEngine/logging/logging.hpp"
#include "GLEngine/io/io.hpp"
#include "GLEngine/graphics/WindowHandler.hpp"
#include "GLEngine/graphics/Renderer.hpp"
#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/graphics/ImageHandler.hpp"
#include "GLEngine/graphics/Model.hpp"
#include "GLEngine/graphics/ModelHandler.hpp"
#include "GLEngine/exceptions.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "stb/stb_image.h"

#include "CPPML/logging/Log.hpp"
#include "CPPML/loading/loading.hpp"
#include "CPPML/loading/OBJ.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <cmath>

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
http://www.cplusplus.com/reference/memory/shared_ptr/~shared_ptr/ // Shared pointer destructor details

http://paulbourke.net/dataformats/obj/
https://en.wikipedia.org/wiki/Wavefront_.obj_file

https://stackoverflow.com/questions/3601602/what-are-rvalues-lvalues-xvalues-glvalues-and-prvalues
*/

int main()
{
    Log::Init();
    CPPML::Log::Init(spdlog::level::trace);

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

    window = windowHandler.CreateWindow(1280, 720, "GLEngine Test Window 1", nullptr, nullptr, windowHintNames, windowHintValues);

    /* Initialize GLEW */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
      std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    }

    /* Print useful information */
    std::cout << "Latest supported OpenGL version on this system is " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEngine is currently using OpenGL version " << GLE_OPENGL_VERSION_MAJOR << "." << GLE_OPENGL_VERSION_MINOR << std::endl;

    std::shared_ptr<Texture> testTexture;
    try { // TODO: Look into cleaner way of doing this, so user of engine doesn't have to manually handle the exception
        testTexture = std::make_shared<Texture>("textures/hugh.png", STBI_rgb, true);
    } catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    Model model = CreateModelFromVBOFile(ResPathRelative("models/hugh.obj").c_str(), testTexture);

    GLuint shaderProgram = CreateShaderProgramFromAddresses(ResPathRelative("shaders/vert1.glsl").c_str(), ResPathRelative("shaders/frag1.glsl").c_str());

    glfwMakeContextCurrent(window); // Note: Only dependance on this line is glDrawElements/glDrawArrays <-- fact check

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    float degree = 0;

    std::cout << "Entering loop..." << std::endl;
    /* Loop */
    while (!windowHandler.ShouldAnyWindowClose())
    {
        degree += 0.01f;
        glm::vec3 objPosition(0.0f, 0.0f, 0.0f);
        glm::vec3 objScale(1.0f, 1.0f, 1.0f);
        glm::vec3 objRotationEuler(0.0f, 0.0f, 0.0f);

        glm::quat objRotationQuat(objRotationEuler);

        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), objPosition);
        glm::mat4 rotationMatrix = glm::toMat4(objRotationQuat);
        glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), objScale);

        glm::mat4 transformationMatrix = translationMatrix * (rotationMatrix * scaleMatrix);

        //glm::vec3 cameraPosition(2.5f, 2.0f, 2.5f);
        glm::vec3 cameraPosition(std::sin(degree)*5, 5.5f, std::cos(degree)*5);

        glm::mat4 cameraMatrix = glm::lookAt(cameraPosition, glm::vec3(0, 3.0f, 0), glm::vec3(0, 1, 0)); // Look into Unity-style camera handling
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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        model.Bind();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvpMatrix"), 1, GL_FALSE, glm::value_ptr(mvpMatrix));
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
        glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, nullptr); // draw with indexing

        glfwSwapBuffers(window); // Make sure to update this window variable when changing between windows
        glfwPollEvents();
    }

    windowHandler.~WindowHandler();
    return 0;
}
