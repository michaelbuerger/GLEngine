#include "GLEngine/graphics/WindowHandler.hpp"
#include "GLEngine/graphics/graphics.hpp"
#include "GLEngine/logging/Log.hpp"
#include "GLEngine/defines.hpp"

#include <iostream>
#include <algorithm>

namespace GLEngine
{

WindowHandler::WindowHandler()
{
    m_windows = std::vector<GLFWwindow *>();

    if (!glfwInit())
    {
        GLE_ENGINE_ERROR("In method \"WindowHandler::WindowHandler\": Failed to initialize GLFW");
        exit(-1); // Change to throwing exception
    }
}

GLFWwindow *WindowHandler::CreateWindow(const int &width, const int &height, const char *title, GLFWmonitor *monitor, GLFWwindow *share, const std::vector<int> &windowHintNames, const std::vector<int> &windowHintValues)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLE_OPENGL_VERSION_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLE_OPENGL_VERSION_MINOR);

    for (size_t i = 0; i < std::min(windowHintNames.size(), windowHintValues.size()); i++)
    {
        glfwWindowHint(windowHintNames.at(i), windowHintValues.at(i));
    }

    GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);
    glfwDefaultWindowHints();
    if (!window)
    {
        GLE_ENGINE_ERROR("In method \"WindowHandler::CreateWindow\": Failed to create window with title \"{}\"", title);
        exit(-1); // Change to throwing exception
    }

    glfwMakeContextCurrent(window);

    m_windows.push_back(window);
    return window;
}

bool WindowHandler::ShouldAnyWindowClose()
{
    for (size_t i = 0; i < m_windows.size(); i++)
    {
        if (glfwWindowShouldClose(m_windows.at(i)))
        {
            return true;
        }
    }
    return false;
}

void WindowHandler::DestroyWindow(GLFWwindow *window)
{
    for (size_t i = 0; i < m_windows.size(); i++) // remove from windows list if applicable
    {
        if (m_windows.at(i) == window)
        {
            m_windows.erase(m_windows.begin() + i);
            break;
        }
    }

    glfwDestroyWindow(window); // destroy window
}

WindowHandler::~WindowHandler()
{
    for (size_t i = 0; i < m_windows.size(); i++)
    {
        glfwDestroyWindow(m_windows.at(i));
    }
    glfwTerminate();
}

} // namespace GLEngine