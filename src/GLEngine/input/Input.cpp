#include "GLEngine/input/Input.hpp"

#include "GLEngine/graphics/graphics.hpp"

#include <glm/glm.hpp>

namespace GLEngine
{

/* --- Keyboard --- */

bool KeyPressed(GLFWwindow *window, const GLEkey &key)
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}
bool KeyHeld(GLFWwindow *window, const GLEkey &key)
{
    return glfwGetKey(window, key) == GLFW_REPEAT; // this apparently isn't even reported unless a key callback is produced
}
bool KeyReleased(GLFWwindow *window, const GLEkey &key)
{
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

/* Sets the key callback for a specific window. Note that polling KeyPressed for this window will be unaffected. */
void SetKeyCallback(GLFWwindow *window, GLEkeyfun callback)
{
    glfwSetKeyCallback(window, callback);
}
void SetNoKeyCallback(GLFWwindow *window)
{
    glfwSetKeyCallback(window, nullptr);
}

/* Sets the char callback for a specific window. */
void SetCharCallback(GLFWwindow *window, GLEcharfun callback)
{
    glfwSetCharCallback(window, callback);
}
void SetNoCharCallback(GLFWwindow *window)
{
    glfwSetCharCallback(window, nullptr);
}

int GetScancodeFromKey(const GLEkey &key)
{
    return glfwGetKeyScancode(key);
}
const char *GetLocalizedKeyName(const GLEkey &key)
{
    return glfwGetKeyName(key, GetScancodeFromKey(key));
}

/* --- Mouse --- */

/* GLE_CURSOR_MODE_WRAP: Uses GLFW's disabled cursor mode, will hide the cursor and lock it to somewhere in the window */
/* TODO: Test what this returns when polling mouse pos (same as callback btw), either mouse pos that isn't limited to the window size or mouse pos delta of last frame */

/* GLE_CURSOR_MODE_NORMAL: Normal mode, GLE_CURSOR_MODE_HIDDEN: Hides the mouse but everything else acts the same */
void SetCursorMode(GLFWwindow *window, const GLEcursormode &cursorMode)
{
    switch (cursorMode)
    {
    case GLE_CURSOR_MODE_NORMAL:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;

    case GLE_CURSOR_MODE_WRAP:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        break;

    case GLE_CURSOR_MODE_HIDDEN:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        break;
    }
}
bool UseRawMouseMotion(GLFWwindow *window)
{ // returns false if the current system doesn't support raw mouse motion
    bool rawSupported = glfwRawMouseMotionSupported();

    if (rawSupported)
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    return rawSupported;
}
bool DontUseRawMouseMotion(GLFWwindow *window)
{ // returns false if the current system doesn't support raw mouse motion
    bool rawSupported = glfwRawMouseMotionSupported();

    if (rawSupported)
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    }

    return rawSupported;
}

glm::vec3 GetCursorPosition(GLFWwindow *window)
{
    glm::vec3 pos;
    double x, y;

    glfwGetCursorPos(window, &x, &y);

    pos.x = x; // implicit conversion double to float
    pos.y = y; // implicit conversion double to float
    return pos;
}
void SetCursorPosition(GLFWwindow *window, const glm::vec3 &pos)
{
    glfwSetCursorPos(window, pos.x, pos.y); // implicit conversions from floats to doubles
}

bool MouseButtonPressed(GLFWwindow *window, const GLEmousebutton &mouseButton)
{
    return glfwGetMouseButton(window, mouseButton) == GLFW_PRESS;
}
bool MouseButtonReleased(GLFWwindow *window, const GLEmousebutton &mouseButton)
{
    return glfwGetMouseButton(window, mouseButton) == GLFW_RELEASE;
}

void SetMouseButtonCallback(GLFWwindow *window, GLEmousebuttonfun callback)
{
    glfwSetMouseButtonCallback(window, callback);
}
void SetCursorPosCallback(GLFWwindow *window, GLEcursorposfun callback)
{
    glfwSetCursorPosCallback(window, callback);
}
void SetCursorEnterCallback(GLFWwindow *window, GLEcursorenterfun callback)
{
    glfwSetCursorEnterCallback(window, callback);
}
void SetScrollCallback(GLFWwindow *window, GLEscrollfun callback)
{
    glfwSetScrollCallback(window, callback);
}
void SetDropCallback(GLFWwindow *window, GLEdropfun callback)
{
    glfwSetDropCallback(window, callback);
}

/* --- Misc --- */

const char *GetClipboard()
{
    return glfwGetClipboardString(nullptr); // Window parameter of this function doesn't matter
}
void SetClipboard(const char *str)
{
    glfwSetClipboardString(nullptr, str); // Window parameter of this function doesn't matter
}

} // namespace GLEngine