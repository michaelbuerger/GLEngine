#include "GLEngine/graphics/graphics.hpp"

#include "GLEngine/defines.hpp"
#include "GLEngine/logging/Log.hpp"
#include "GLEngine/io/io.hpp"
#include "GLEngine/graphics/WindowHandler.hpp"
#include "GLEngine/graphics/Renderer.hpp"
#include "GLEngine/graphics/Texture.hpp"
#include "GLEngine/graphics/Material.hpp"
#include "GLEngine/graphics/Model.hpp"
#include "GLEngine/graphics/GameObject.hpp"
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
#include <glm/gtc/quaternion.hpp>

#include "stb/stb_image.h"

#include "CPPML/logging/Log.hpp"
#include "CPPML/loading/loading.hpp"
#include "CPPML/loading/OBJ.hpp"

#include <imgui/imgui.h> // the GLEngine way of including things, #include "imgui.h" works too for compatibility with the lib

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <memory>
#include <cmath>
#include <sstream>

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

/*
REFACTOR:
- [X] Texture --> material
- [X] Get rid of references to texture in model
- [X] GameObject --> model + material + Transform
- [ ] Renderer --> Takes in list of GameObjects
*/

/*
- [X] Time.deltaTime equivalent
- [X] Bouncy ball
- [ ] Batched/indexed (better) rendering
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

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

    window = windowHandler.CreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GLEngine", nullptr, nullptr, windowHintNames, windowHintValues);

    /* Initialize GLEW */
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
    }

    /* OPENGL CONTEXT */
    glfwMakeContextCurrent(window); // TODO: Figure out dependance on this line (like what code needs the context)

    /* RENDER */
    Renderer::Init();

    /* Setup Dear ImGui context */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    /* Dear ImGui style */
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();
    // ImGui::StyleColorsLight();

    /* Load ImGui fonts */
    // use default font for now

    /* Print useful information */
    std::cout << "GLEngine is currently using OpenGL version " << GLE_OPENGL_VERSION_MAJOR << "." << GLE_OPENGL_VERSION_MINOR << std::endl;

    /* TEXTURES */
    std::shared_ptr<Texture> concreteTexture;
    std::shared_ptr<Texture> framedWhiteTexture;
    std::shared_ptr<Texture> allWhiteTexture;
    std::shared_ptr<Texture> testTexture;
    std::shared_ptr<Texture> hughTexture;
    std::shared_ptr<Texture> lilFrogDiffuseTexture;
    std::shared_ptr<Texture> lilFrogSpecularTexture;
    try
    { // TODO: Look into cleaner way of doing this, so user of engine doesn't have to manually handle the exception
        concreteTexture = std::make_shared<Texture>(ResPathRelative("textures/concrete.png").c_str(), STBI_rgb, true);
        framedWhiteTexture = std::make_shared<Texture>(ResPathRelative("textures/framed-white.png").c_str(), STBI_rgb, true);
        allWhiteTexture = std::make_shared<Texture>(ResPathRelative("textures/solid-white.png").c_str(), STBI_rgb, true);
        testTexture = std::make_shared<Texture>(ResPathRelative("textures/test-texture.png").c_str(), STBI_rgb, true);
        hughTexture = std::make_shared<Texture>(ResPathRelative("textures/hugh.png").c_str(), STBI_rgb, true);
        lilFrogDiffuseTexture = std::make_shared<Texture>(ResPathRelative("textures/lil-frog-diffuse.png").c_str(), STBI_rgb, true);
        lilFrogSpecularTexture = std::make_shared<Texture>(ResPathRelative("textures/lil-frog-specular.png").c_str(), STBI_rgb, true);
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        exit(-1);
    }

    std::shared_ptr<ShaderProgram> shaderProgram = std::make_shared<ShaderProgram>(ResPathRelative("shaders/vert1.vert").c_str(), ResPathRelative("shaders/frag1.frag").c_str());
    std::shared_ptr<ShaderProgram> simpleDepthShader = std::make_shared<ShaderProgram>(ResPathRelative("shaders/depth-vert1.vert").c_str(), ResPathRelative("shaders/depth-frag1.frag").c_str());

    /* MATERIALS */
    bool unlit1 = false;
    std::shared_ptr<Material> shinyOrangeMaterial = std::make_shared<Material>(nullptr, nullptr, shaderProgram, unlit1, 256, false, glm::vec3(0.925f, 0.607f, 0.015f));
    std::shared_ptr<Material> concreteMaterial = std::make_shared<Material>(concreteTexture, allWhiteTexture, shaderProgram, unlit1, 32);
    std::shared_ptr<Material> testMaterial1 = std::make_shared<Material>(testTexture, allWhiteTexture, shaderProgram, unlit1, 256);
    std::shared_ptr<Material> shinyPurpleMaterial = std::make_shared<Material>(nullptr, nullptr, shaderProgram, unlit1, 256, false, glm::vec3(0.8f, 0.1f, 0.5f));
    std::shared_ptr<Material> hughMaterial = std::make_shared<Material>(hughTexture, allWhiteTexture, shaderProgram, unlit1, 256);

    // when using lil-frog-specular, the texture appears all white, idk why
    std::shared_ptr<Material> lilFrogMaterial = std::make_shared<Material>(lilFrogDiffuseTexture, allWhiteTexture, shaderProgram, unlit1, 128);
    std::shared_ptr<Material> framedWhiteMaterial = std::make_shared<Material>(framedWhiteTexture, allWhiteTexture, shaderProgram, unlit1, 256);

    /* MODELS */
    std::shared_ptr<Model> cube = std::make_shared<Model>(CreateModelFromOBJFile(ResPathRelative("models/cube.obj").c_str()));
    std::shared_ptr<Model> plane = std::make_shared<Model>(CreateModelFromOBJFile(ResPathRelative("models/plane.obj").c_str()));
    std::shared_ptr<Model> sphere = std::make_shared<Model>(CreateModelFromOBJFile(ResPathRelative("models/smoothsphere.obj").c_str()));
    std::shared_ptr<Model> dog = std::make_shared<Model>(CreateModelFromOBJFile(ResPathRelative("models/dog.obj").c_str()));
    std::shared_ptr<Model> hugh = std::make_shared<Model>(CreateModelFromOBJFile(ResPathRelative("models/hugh.obj").c_str()));
    std::shared_ptr<Model> lilFrog = std::make_shared<Model>(CreateModelFromOBJFile(ResPathRelative("models/lil-frog.obj").c_str()));

    /* SCENE */
    Camera camera = Camera(Transform(glm::vec3(0.0f, 10.0f, 10.0f), glm::vec3(-45.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f)),
                           90.0f, 16.0f / 9.0f, 100000000.0f, GLE_CAMERA_MODE_PERSPECTIVE); // scale doesn't affect the camera


    GameObject bouncyBallInstance = GameObject(cube, shinyPurpleMaterial, Transform());

    uint bouncyBallsCount = 512;
    std::vector<Transform> bouncyBallTransforms(bouncyBallsCount);
    std::vector<glm::mat4> bouncyBallTransformationMatrices(bouncyBallsCount);
    std::vector<glm::vec3> bouncyBallVelocities(bouncyBallsCount);

    float boundsDist = 15.0f;

    std::shared_ptr<ShaderProgram> shaderProgramDispShadowMap = std::make_shared<ShaderProgram>(ResPathRelative("shaders/disp-shadowmap/vert1.vert").c_str(), ResPathRelative("shaders/disp-shadowmap/frag1.frag").c_str());
    auto transformDispShadowMap = Transform();
    transformDispShadowMap.SetScale(glm::vec3(5.0f, 1.0f, 5.0f));
    transformDispShadowMap.SetPosition(glm::vec3(boundsDist+transformDispShadowMap.GetScale().x, 0.0f, 0.0f));

    float minX = -boundsDist, maxX = boundsDist,
    minY = 2.0f, maxY = boundsDist,
    minZ = -boundsDist, maxZ = boundsDist;
    float minBallScale = 0.5f, maxBallScale = 0.5f;

    GameObject ground = GameObject(plane, testMaterial1, Transform(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(boundsDist, 1.0f, boundsDist)));
    ground.material->tiling = glm::vec2((int)boundsDist, (int)boundsDist); // sets tiling multiplier, affects anything referencing this material
    
    GameObject testCube1 = GameObject(cube, shinyPurpleMaterial, Transform());
    testCube1.transform.SetPositionY(3.0f);

    for(uint i=0; i<bouncyBallsCount; i++)
    {
        glm::vec3 ballPosition = glm::vec3((float)randomRange(minX, maxX), (float)randomRange(minY, maxY), (float)randomRange(minZ, maxZ));
        glm::vec3 ballRotation = glm::vec3((float)randomRange(0, 360), (float)randomRange(0, 360), (float)randomRange(0, 360));
        float ballScale = randomRange(minBallScale, maxBallScale);

        // create bouncy ball with given ballPosition, ballScale, and default velocity of vec3(zero)
        bouncyBallTransforms.at(i) = Transform(ballPosition, ballRotation*glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(ballScale, ballScale, ballScale));
        bouncyBallTransformationMatrices.at(i) = bouncyBallTransforms.at(i).GetMatrix();
        bouncyBallVelocities.at(i) = VEC3F_ZERO;
    }

    // Point lights initialization
    PointLight pointLight0 = PointLight(glm::vec3(5.0f, 12.0f, 5.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    PointLight pointLight1 = PointLight(glm::vec3(-5.0f, 8.0f, 5.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    PointLight pointLight2 = PointLight(glm::vec3(5.0f, 8.0f, -5.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    PointLight pointLight3 = PointLight(glm::vec3(-5.0f, 8.0f, -5.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);

    // Directional lights initialization
    DirectionalLight directionalLight0 = DirectionalLight(glm::vec3(-10.0f, -10.0f, -10.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.7f, 0.7f, 0.7f), glm::vec3(0.9f, 0.9f, 0.9f));

    // Spot lights initialization
    SpotLight spotLight0 = SpotLight(camera.transform.GetPosition(), camera.transform.GetForward(), 12.5f, 25.5f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f);

    /* GAME LOOP VARIABLES */
    glm::vec3 playerForward = camera.transform.GetForward();
    glm::vec3 playerRight = camera.transform.GetRight();
    glm::vec3 playerUp = camera.transform.GetRight();

    glm::vec3 previousCursorPosition;
    glm::vec3 currentCursorPosition;
    glm::vec3 cursorPositionDelta;

    float playerTranslateSpeed = 10.0f;
    float playerRollSpeed = 120.0f;
    float playerSensitivity = 10.0f;

    /* 6DOF CAMERA */
    SetCursorMode(window, GLE_CURSOR_MODE_WRAP);
    UseRawMouseMotion(window);

    // for filtering out first n cursorPositions as they give random values for first 1 or 2 calls when cursorMode disabled
    // this is a GLFW issue that has not been solved for like 3 years for some reason, maybe I can go fix it myself at some point
    // could also write wrapper methods for handling cursor position deltas for similar use cases that handles this
    int cursorPositionRequestCount = 0;
    int cursorPositionRequestThreshold = 2; // 2 == ignore first two calls

    /* SHADOW STUFF SETUP */
    const uint SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

    uint depthmapTextureID;
    glGenTextures(1, &depthmapTextureID);
    glBindTexture(GL_TEXTURE_2D, depthmapTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    uint depthmapFBO;
    glGenFramebuffers(1, &depthmapFBO);

    glBindFramebuffer(GL_FRAMEBUFFER, depthmapFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthmapTextureID, 0);
    glDrawBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    float shadowBounds = 30.0f;
    float near_plane = -shadowBounds, far_plane = shadowBounds;
    glm::mat4 lightProjection = glm::ortho(-shadowBounds, shadowBounds, -shadowBounds, shadowBounds, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(-directionalLight0.direction, VEC3F_ZERO, VEC3F_UP);
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    Renderer::shaderProgramSubstitutePtr = simpleDepthShader;


    /* TIME */
    double lastFrameTime = 0.0;
    double currentFrameTime = 0.0;
    float deltaTime = 0.0; // time in seconds between last frame and current frame (multiply by speeds to get per second movement)
    std::stringstream windowTitle;

    std::cout << "Entering loop..." << std::endl;
    /* Loop */
    while (!windowHandler.ShouldAnyWindowClose())
    {
        /* CALC DELTA TIME */
        lastFrameTime = currentFrameTime;
        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;

        /* DISPLAY FPS WINDOW TITLE */
        windowTitle << "GLEngine [" << (int) std::floor(1/deltaTime) << " FPS]";
        glfwSetWindowTitle(window, windowTitle.str().c_str());
        windowTitle.str(std::string()); // end-result same as .str(""), but more efficient on some compilers
        windowTitle.clear();

        playerForward = camera.transform.GetForward();
        playerRight = camera.transform.GetRight();
        playerUp = camera.transform.GetRight();

        if(KeyPressed(window, GLE_KEY_A) || KeyPressed(window, GLE_KEY_LEFT)) { camera.transform.Translate(playerRight * -playerTranslateSpeed * deltaTime); }
        else if(KeyPressed(window, GLE_KEY_D) || KeyPressed(window, GLE_KEY_RIGHT)) { camera.transform.Translate(playerRight * playerTranslateSpeed * deltaTime); }

        if(KeyPressed(window, GLE_KEY_W) || KeyPressed(window, GLE_KEY_UP)) { camera.transform.Translate(playerForward * playerTranslateSpeed * deltaTime); }
        else if(KeyPressed(window, GLE_KEY_S) || KeyPressed(window, GLE_KEY_DOWN)) { camera.transform.Translate(playerForward * -playerTranslateSpeed * deltaTime); }

        if(KeyPressed(window, GLE_KEY_Q)) { camera.transform.Rotate(0.0f, 0.0f, -playerRollSpeed * deltaTime); }
        else if(KeyPressed(window, GLE_KEY_E)) { camera.transform.Rotate(0.0f, 0.0f, playerRollSpeed * deltaTime); }

        if(KeyPressed(window, GLE_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, true); // force close
        }

        previousCursorPosition = currentCursorPosition;
        currentCursorPosition = GetCursorPosition(window);
        cursorPositionDelta = currentCursorPosition - previousCursorPosition;

        if(cursorPositionRequestCount <= cursorPositionRequestThreshold)
        {
            cursorPositionDelta = VEC3F_ZERO; // ignore delta
            cursorPositionRequestCount++;
        }

        camera.transform.Rotate(-cursorPositionDelta.y * playerSensitivity * deltaTime, cursorPositionDelta.x * playerSensitivity * deltaTime, 0.0f);

        // z-roll happens
        // need to further investigate control schemes (e.g. fps cam where y rotation occurs purely on WORLD y axis and there is no z rot)

        //std::cout << camera.transform.DebugStr() << std::endl << std::endl;

        // matrices that don't change with the model transform
        shaderProgram->UniformMat4("projectionMatrix", camera.GetProjectionMatrix());
        shaderProgram->UniformMat4("viewMatrix", camera.GetViewMatrix());
        shaderProgram->UniformVec3("viewPos", camera.transform.GetPosition());

        /*shaderProgram->UniformMat4("projectionMatrix", lightProjection);
        shaderProgram->UniformMat4("viewMatrix", lightView);
        shaderProgram->UniformVec3("viewPos", -directionalLight0.direction);*/

        // Lights generic
        shaderProgram->UniformInt("directionalLightCount", 1);
        shaderProgram->UniformInt("pointLightCount", 0);
        shaderProgram->UniformInt("spotLightCount", 0);

        // Point lights uniform
        pointLight0.Uniform(*shaderProgram, 0);
        pointLight1.Uniform(*shaderProgram, 1);
        pointLight2.Uniform(*shaderProgram, 2);
        pointLight3.Uniform(*shaderProgram, 3);

        // Directional lights uniform
        directionalLight0.Uniform(*shaderProgram, 0);

        spotLight0.position = camera.transform.GetPosition();
        spotLight0.direction = playerForward;
        // Spot lights uniform
        spotLight0.Uniform(*shaderProgram, 0);

        /* PHYSICS */
        if(KeyPressed(window, GLE_KEY_P))
        {
        for(int i=0; i<bouncyBallsCount; i++)
        {
            /* BOUNCY BALLS PHYSICS */
            float gravityConstant = 9.81f;
            float collisionVelocityMultiplier = 0.5f;

            float sphereRadius = bouncyBallTransforms[i].GetScale().y;
            // sphereRadius *= 2.35f; // for frogs

            // Collision
            if(bouncyBallTransforms.at(i).GetPosition().y - sphereRadius <= ground.transform.GetPosition().y) // "collision" with ground
            {
                bouncyBallTransforms.at(i).SetPositionY(ground.transform.GetPosition().y + sphereRadius);
                bouncyBallVelocities.at(i) *= glm::vec3(0.0f, -collisionVelocityMultiplier, 0.0f);
            }

            // Step
            bouncyBallVelocities.at(i) += glm::vec3(0.0f, -2.0*gravityConstant * deltaTime /* * randomRange(0.7f, 1.0f) */, 0.0f);
            bouncyBallTransforms.at(i).Translate(bouncyBallVelocities.at(i) * deltaTime);

            // update matrices
            bouncyBallTransformationMatrices.at(i) = bouncyBallTransforms.at(i).GetMatrix();
        }
        }

        /* RENDER */
        
        /* SHADOW RENDER */

        /* SCENE RENDER 1 */
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, depthmapFBO);
            glClear(GL_DEPTH_BUFFER_BIT);
            Renderer::subShaderProgram = true;
            //simpleDepthShader->UniformMat4("lightSpaceMatrix", lightSpaceMatrix);
            simpleDepthShader->UniformMat4("lightSpaceMatrix", lightSpaceMatrix);
            Renderer::Render(testCube1);
            Renderer::Render(ground);
            Renderer::RenderInstanced(bouncyBallInstance, bouncyBallTransformationMatrices.data(), bouncyBallsCount);
            Renderer::subShaderProgram = false;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        /* SCENE RENDER 2 */
        glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        Renderer::Update();
        shaderProgramDispShadowMap->Bind();
        plane->Bind();

        glActiveTexture(GLE_MATERIAL_DIFFUSE_TEX_SLOT);
        glBindTexture(GL_TEXTURE_2D, concreteTexture->GetGLID());
        glActiveTexture(GLE_SHADOWMAP_TEX_SLOT);
        glBindTexture(GL_TEXTURE_2D, depthmapTextureID);
        shaderProgramDispShadowMap->UniformMat4("projectionMatrix", camera.GetProjectionMatrix());
        shaderProgramDispShadowMap->UniformMat4("viewMatrix", camera.GetViewMatrix());
        shaderProgramDispShadowMap->UniformMat4("modelMatrix", transformDispShadowMap.GetMatrix());
        shaderProgramDispShadowMap->UniformInt("shadowMap", GLE_SHADOWMAP_UNIFORM_ID);

        glDrawElements(GL_TRIANGLES, plane->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);

        shaderProgram->UniformMat4("lightSpaceMatrix", lightSpaceMatrix);
        shaderProgram->UniformInt("shadowMap", GLE_SHADOWMAP_UNIFORM_ID);
        Renderer::Render(ground);
        Renderer::Render(testCube1);
        Renderer::RenderInstanced(bouncyBallInstance, bouncyBallTransformationMatrices.data(), bouncyBallsCount);

        /* ----- */
        glfwSwapBuffers(window); // Swap front and back buffer, make sure to update this window variable when changing between windows
        glfwPollEvents();
        Renderer::Update();
    }

    return 0;
}
