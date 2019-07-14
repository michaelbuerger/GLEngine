#include "GLEngine/graphics/WindowHandler.hpp"
#include "GLEngine/graphics/graphics.hpp"

#include <iostream>
#include <algorithm>

namespace GLEngine { namespace graphics {

    WindowHandler::WindowHandler()
    {
        windows = std::vector<GLFWwindow*>();

        if(!glfwInit())
        {
            std::cout << "Failed to initialize GLFW" << std::endl;
            exit(-1); // Update to use logging
        }
    }

    GLFWwindow *WindowHandler::CreateWindow(const int& width, const int& height, const char *title, GLFWmonitor *monitor, GLFWwindow *share, const std::vector<int>& windowHintNames, const std::vector<int>& windowHintValues)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        for (size_t i=0; i<std::min(windowHintNames.size(), windowHintValues.size()); i++)
        {
            glfwWindowHint(windowHintNames.at(i), windowHintValues.at(i));
        }

        GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);
        glfwDefaultWindowHints();
        if (!window)
        {
            std::cout << "Failed to create window \"" << title << "\"" << std::endl;
            exit(-1); // Update to use logging
        }

        glfwMakeContextCurrent(window);

        windows.push_back(window);
        return window;
    }

    bool WindowHandler::ShouldAnyWindowClose()
    {
        for (size_t i=0; i<this->windows.size(); i++)
        {
            if(glfwWindowShouldClose(this->windows.at(i)))
            {
                return true;
            }
        }
        return false;
    }

    void WindowHandler::DestroyWindow(GLFWwindow *window)
    {
        for (size_t i=0; i<this->windows.size(); i++) // remove from windows list if applicable
        {
            if(this->windows.at(i) == window)
            {
                this->windows.erase(this->windows.begin()+i);
                break;
            }
        }

        glfwDestroyWindow(window); // destroy window
    }

    WindowHandler::~WindowHandler()
    {
        for (size_t i=0; i<this->windows.size(); i++)
        {
            glfwDestroyWindow(this->windows.at(i));
        }
        glfwTerminate();
    }

}}