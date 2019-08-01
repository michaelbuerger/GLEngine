# Getting Started
**First of all, make sure you follow the installation instructions [here](../#installation).**

---
## GLFW and OpenGL (with glew)

GLEngine uses [GLFW 3.3](https://www.glfw.org/) for platform-independent window and input handling, and [glew 2.1.0](http://glew.sourceforge.net/) for including modern OpenGL functionality. They must be included in the following order:
``` cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
```

!!! tip
    Any time you want to use GLFW or OpenGL methods or defines, simply importing ```GLEngine/include/graphics/graphics.hpp``` will include everything for you in the right order.

---
## Creating Windows

If you want to manually handle the creation and destruction of GLFW windows, please take a look at the following:
[GLFW Window Guide](https://www.glfw.org/docs/latest/window_guide.html)

GLEngine contains it's own system for creating and handling one or multiple GLFW windows called the [WindowHandler](reference/graphics.md/#WindowHandler). You should only create one of these per application. The following snippet shows you how to create your own WindowHandler (initializing GLFW for you) and then create your own window.

``` cpp
WindowHandler windowHandler = WindowHandler();
// Initialize GLFW and WindowHandler

std::vector<int> windowHintNames = std::vector<int>();
std::vector<int> windowHintValues = std::vector<int>();

windowHintNames.push_back(GLFW_RESIZABLE);
windowHintValues.push_back(GL_FALSE); // Turn off resizing

windowHintNames.push_back(GLFW_CONTEXT_VERSION_MAJOR);
windowHintValues.push_back(3); // OpenGL version 3.x

windowHintNames.push_back(GLFW_CONTEXT_VERSION_MINOR);
windowHintValues.push_back(3); // OpenGL version x.3
// Together these two window hints set the Window to use OpenGL version 3.3

GLFWwindow *window; = windowHandler.CreateWindow(1280, 720, "Window Title", 
nullptr, nullptr, windowHintNames, windowHintValues);
```

[See the WindowHandler reference for more details](../reference/graphics/#windowhandler)

Every window holds a reference to it's own OpenGL version, as the OpenGL context at any time in your application is based on what window you are rendering to.

!!! note
    ```CreateWindow``` will call ```glfwMakeContentCurrent``` on the ```GLFWwindow*``` it is creating for you. When you want to manually switch the glfw context, you have to call ```glfwMakeContextCurrent(yourWindow)``` yourself.

---
## Initializing glew

At any point after the [initialization of GLFW](#creating-windows), you can initialize glew. This can be achieved with the following code (eventually this will be handled by the renderer):

``` cpp
GLenum err = glewInit();
if (GLEW_OK != err)
{
    std::cout << "Error: " << glewGetErrorString(err) << std::endl;
}
```

!!! note
    Please note that you should try to use GLEngine's logging (with [spdlog](https://github.com/gabime/spdlog)) when possible. See the [engine and application logging](#engine-and-application-logging) section.

---
## Engine and Application Logging

GLEngine utilizes [spdlog](https://github.com/gabime/spdlog) to handle all of it's logging. [CPPModelLibrary](https://github.com/popwser/CPPModelLibrary) also does.  
This is because spdlog handles two important features: [Rust-lang like formatting](https://doc.rust-lang.org/1.6.0/std/macro.println!.html), and level based logging: meaning that all logging can separated into different levels of importance (and colors!).