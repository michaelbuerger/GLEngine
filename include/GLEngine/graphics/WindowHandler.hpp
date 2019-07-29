#ifndef GLE_WINDOW_HANDLER_CPP
#define GLE_WINDOW_HANDLER_CPP

#include "GLEngine/graphics/graphics.hpp"
#include <vector>
#include <string>

namespace GLEngine { namespace graphics {

    class WindowHandler
    {
        private:
            std::vector<GLFWwindow*> windows; 
            
        public:
            /* Initializes GLFW */
            WindowHandler();

            /* Creates GLFW window with default version of OpenGL 3.3, Initializes GLEW.
            If window hint vectors are not null this can be overriden */
            GLFWwindow *CreateWindow(const int& width, const int& height, const char *title, GLFWmonitor *monitor, GLFWwindow *share, const std::vector<int>& windowHintNames, const std::vector<int>& windowHintValues);
            bool ShouldAnyWindowClose();
            void DestroyWindow(GLFWwindow *window);

            /* Destroys all windows */
            ~WindowHandler();
    };

}}

#endif