#include "GLEngine/graphics/graphics.hpp"

#define GLE_RESOURCES_PATH "/home/michaelbuerger/Documents/Programming Projects/GLEngine/resources/"
#include "GLEngine/defines.hpp"
#include "GLEngine/logging/Log.hpp"
#include "GLEngine/io/io.hpp"
#include "GLEngine/graphics/WindowHandler.hpp"
#include "GLEngine/graphics/Renderer.hpp"
#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/graphics/Model.hpp"
#include "GLEngine/graphics/ModelLoading.hpp"
#include "GLEngine/graphics/Transform.hpp"
#include "GLEngine/graphics/Camera.hpp"
#include "GLEngine/graphics/ShaderProgram.hpp"
#include "GLEngine/graphics/PointLight.hpp"
#include "GLEngine/graphics/DirectionalLight.hpp"
#include "GLEngine/graphics/SpotLight.hpp"
#include "GLEngine/exceptions.hpp"
#include "GLEngine/math/math.hpp"
#include "GLEngine/input/Input.hpp"

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

3rd Party GUI:
https://github.com/ocornut/imgui
*/

int main()
{
    Log::Init(spdlog::level::trace);
    CPPML::Log::Init(spdlog::level::trace);

    WindowHandler windowHandler = WindowHandler();
    // WindowHandler windowHandler(); <-- does not call default constructor for some reason

    GLFWwindow *window;

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

    /* --- --- */
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f, 2.0f, -2.5f),
        glm::vec3(1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)};

    glm::vec3 pointLightPositions[] = {
        glm::vec3(0.7f, 0.2f, 2.0f),
        glm::vec3(2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f, 2.0f, -12.0f),
        glm::vec3(0.0f, 0.0f, -3.0f)};

    // Note: Diffuse map is multiplied by ambient and diffuse lighting, Specular is only for specular
    // Diffuse map can be used for both maps and it would be effectively equivalent to the old kind of texture handling
    std::shared_ptr<Texture> diffuseMap;
    try
    { // TODO: Look into cleaner way of doing this, so user of engine doesn't have to manually handle the exception
        diffuseMap = std::make_shared<Texture>(ResPathRelative("textures/container-diffuse.png").c_str(), GL_TEXTURE0, STBI_rgb, true);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    std::shared_ptr<Texture> specularMap;
    try
    { // TODO: Look into cleaner way of doing this, so user of engine doesn't have to manually handle the exception
        specularMap = std::make_shared<Texture>(ResPathRelative("textures/container-specular.png").c_str(), GL_TEXTURE1, STBI_rgb, true);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    Model model = CreateModelFromOBJFile(ResPathRelative("models/cube.obj").c_str(), diffuseMap);

    ShaderProgram shaderProgram = ShaderProgram(ResPathRelative("shaders/vert1.glsl").c_str(), ResPathRelative("shaders/frag1.glsl").c_str());

    glfwMakeContextCurrent(window); // TODO: Figure out dependance on this line (like what code needs the context)

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Transform transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    Camera camera = Camera(Transform(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
                           90.0f, 16.0f / 9.0f, 100000000.0f, GLE_CAMERA_MODE_PERSPECTIVE); // scale doesn't affect the camera

    // Point lights initialization
    PointLight pointLight0 = PointLight(pointLightPositions[0], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    PointLight pointLight1 = PointLight(pointLightPositions[1], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    PointLight pointLight2 = PointLight(pointLightPositions[2], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    PointLight pointLight3 = PointLight(pointLightPositions[3], glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);

    // Directional lights initialization
    DirectionalLight directionalLight0 = DirectionalLight(glm::vec3(1.2f, 1.0f, 2.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f));

    // Spot lights initialization
    SpotLight spotLight0 = SpotLight(camera.transform.GetPosition(), glm::vec3(0.0f, 0.0f, -1.0f), 12.5f, 25.5f, glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);

    std::cout << "Entering loop..." << std::endl;
    /* Loop */
    while (!windowHandler.ShouldAnyWindowClose())
    {
        //transform.Rotate(glm::vec3(0.0f, 0.5f, 0.0f));

        if (KeyPressed(window, GLE_KEY_A))
        {
            camera.transform.Translate(glm::vec3(-0.03f, 0.0f, 0.0f));
        }
        else if (KeyPressed(window, GLE_KEY_D))
        {
            camera.transform.Translate(glm::vec3(0.03f, 0.0f, 0.0f));
        }
        if (KeyPressed(window, GLE_KEY_W))
        {
            camera.transform.Translate(glm::vec3(0.0f, 0.0f, -0.3f));
        }
        else if (KeyPressed(window, GLE_KEY_S))
        {
            camera.transform.Translate(glm::vec3(0.0f, 0.0f, 0.3f));
        }
        if (KeyPressed(window, GLE_KEY_Q))
        {
            camera.transform.Rotate(glm::vec3(0.0f, 1.0f, 0.0f));
        }
        else if (KeyPressed(window, GLE_KEY_E))
        {
            camera.transform.Rotate(glm::vec3(0.0f, -1.0f, 0.0f));
        }

        shaderProgram.Bind();
        model.BindVAO();

        // matrices that don't change with the model transform
        shaderProgram.UniformMat4("projectionMatrix", camera.GetProjectionMatrix());
        shaderProgram.UniformMat4("viewMatrix", camera.GetViewMatrix());
        shaderProgram.UniformVec3("viewPos", camera.transform.GetPosition());

        // Lights generic
        shaderProgram.UniformInt("directionalLightCount", 1);
        shaderProgram.UniformInt("pointLightCount", 4);
        shaderProgram.UniformInt("spotLightCount", 1);

        // Point lights uniform
        pointLight0.Uniform(shaderProgram, 0);
        pointLight1.Uniform(shaderProgram, 1);
        pointLight2.Uniform(shaderProgram, 2);
        pointLight3.Uniform(shaderProgram, 3);

        // Directional lights uniform
        directionalLight0.Uniform(shaderProgram, 0);

        spotLight0.position = camera.transform.GetPosition();
        // Spot lights uniform
        spotLight0.Uniform(shaderProgram, 0);

        // Material
        shaderProgram.UniformInt("material.diffuseMap", 0);
        shaderProgram.UniformInt("material.specularMap", 1);
        model.BindTexture();
        specularMap->Bind();
        shaderProgram.UniformVec3("material.color", glm::vec3(1.0f, 0.0f, 0.0f));
        shaderProgram.UniformFloat("material.shininess", 128);
        shaderProgram.UniformBool("material.useTexture", GL_TRUE);
        shaderProgram.UniformBool("material.unlit", GL_FALSE);

        for (unsigned int i = 0; i < 10; i++)
        {
            transform.SetPosition(cubePositions[i]);
            transform.SetRotation(glm::vec3(20.0f * i, 20.0f * i, 20.0f * i));

            // matrices that do change with the model transform
            shaderProgram.UniformMat4("modelMatrix", transform.GetMatrix());
            shaderProgram.UniformMat4("normalMatrix", transform.GetNormalMatrix());

            // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe
            glDrawElements(GL_TRIANGLES, model.GetVertexCount(), GL_UNSIGNED_INT, nullptr); // draw with indexing
        }

        glfwSwapBuffers(window); // Make sure to update this window variable when changing between windows
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();
    }

    return 0;
}
