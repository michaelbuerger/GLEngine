#ifndef GLE_INPUT_HPP
#define GLE_INPUT_HPP

#include "GLEngine/graphics/graphics.hpp"

#include <glm/glm.hpp>

#include <functional>

namespace GLEngine
{

/* --- Keyboard --- */

enum GLEkey
{
    GLE_KEY_UNKNOWN = GLFW_KEY_UNKNOWN, // Any unknown key
    GLE_KEY_SPACE = GLFW_KEY_SPACE,
    GLE_KEY_APOSTROPHE = GLFW_KEY_APOSTROPHE,
    GLE_KEY_COMMA = GLFW_KEY_COMMA,
    GLE_KEY_MINUS = GLFW_KEY_MINUS,
    GLE_KEY_PERIOD = GLFW_KEY_PERIOD,
    GLE_KEY_SLASH = GLFW_KEY_SLASH,
    GLE_KEY_0 = GLFW_KEY_0,
    GLE_KEY_1 = GLFW_KEY_1,
    GLE_KEY_2 = GLFW_KEY_2,
    GLE_KEY_3 = GLFW_KEY_3,
    GLE_KEY_4 = GLFW_KEY_4,
    GLE_KEY_5 = GLFW_KEY_5,
    GLE_KEY_6 = GLFW_KEY_6,
    GLE_KEY_7 = GLFW_KEY_7,
    GLE_KEY_8 = GLFW_KEY_8,
    GLE_KEY_9 = GLFW_KEY_9,
    GLE_KEY_SEMICOLON = GLFW_KEY_SEMICOLON,
    GLE_KEY_EQUAL = GLFW_KEY_EQUAL,
    GLE_KEY_A = GLFW_KEY_A,
    GLE_KEY_B = GLFW_KEY_B,
    GLE_KEY_C = GLFW_KEY_C,
    GLE_KEY_D = GLFW_KEY_D,
    GLE_KEY_E = GLFW_KEY_E,
    GLE_KEY_F = GLFW_KEY_F,
    GLE_KEY_G = GLFW_KEY_G,
    GLE_KEY_H = GLFW_KEY_H,
    GLE_KEY_I = GLFW_KEY_I,
    GLE_KEY_J = GLFW_KEY_J,
    GLE_KEY_K = GLFW_KEY_K,
    GLE_KEY_L = GLFW_KEY_L,
    GLE_KEY_M = GLFW_KEY_M,
    GLE_KEY_N = GLFW_KEY_N,
    GLE_KEY_O = GLFW_KEY_O,
    GLE_KEY_P = GLFW_KEY_P,
    GLE_KEY_Q = GLFW_KEY_Q,
    GLE_KEY_R = GLFW_KEY_R,
    GLE_KEY_S = GLFW_KEY_S,
    GLE_KEY_T = GLFW_KEY_T,
    GLE_KEY_U = GLFW_KEY_U,
    GLE_KEY_V = GLFW_KEY_V,
    GLE_KEY_W = GLFW_KEY_W,
    GLE_KEY_X = GLFW_KEY_X,
    GLE_KEY_Y = GLFW_KEY_Y,
    GLE_KEY_Z = GLFW_KEY_Z,
    GLE_KEY_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
    GLE_KEY_BACKSLASH = GLFW_KEY_BACKSLASH,
    GLE_KEY_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
    GLE_KEY_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT, // `
    GLE_KEY_WORLD_1 = GLFW_KEY_WORLD_1,           // non-US #1
    GLE_KEY_WORLD_2 = GLFW_KEY_WORLD_2,           // non-US #2
    GLE_KEY_ESCAPE = GLFW_KEY_ESCAPE,
    GLE_KEY_ENTER = GLFW_KEY_ENTER,
    GLE_KEY_TAB = GLFW_KEY_TAB,
    GLE_KEY_BACKSPACE = GLFW_KEY_BACKSPACE,
    GLE_KEY_INSERT = GLFW_KEY_INSERT,
    GLE_KEY_DELETE = GLFW_KEY_DELETE,
    GLE_KEY_RIGHT = GLFW_KEY_RIGHT,
    GLE_KEY_LEFT = GLFW_KEY_LEFT,
    GLE_KEY_DOWN = GLFW_KEY_DOWN,
    GLE_KEY_UP = GLFW_KEY_UP,
    GLE_KEY_PAGE_UP = GLFW_KEY_PAGE_UP,
    GLE_KEY_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
    GLE_KEY_HOME = GLFW_KEY_HOME,
    GLE_KEY_END = GLFW_KEY_END,
    GLE_KEY_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
    GLE_KEY_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
    GLE_KEY_NUM_LOCK = GLFW_KEY_NUM_LOCK,
    GLE_KEY_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
    GLE_KEY_PAUSE = GLFW_KEY_PAUSE,
    GLE_KEY_F1 = GLFW_KEY_F1,
    GLE_KEY_F2 = GLFW_KEY_F2,
    GLE_KEY_F3 = GLFW_KEY_F3,
    GLE_KEY_F4 = GLFW_KEY_F4,
    GLE_KEY_F5 = GLFW_KEY_F5,
    GLE_KEY_F6 = GLFW_KEY_F6,
    GLE_KEY_F7 = GLFW_KEY_F7,
    GLE_KEY_F8 = GLFW_KEY_F8,
    GLE_KEY_F9 = GLFW_KEY_F9,
    GLE_KEY_F10 = GLFW_KEY_F10,
    GLE_KEY_F11 = GLFW_KEY_F11,
    GLE_KEY_F12 = GLFW_KEY_F12,
    GLE_KEY_F13 = GLFW_KEY_F13,
    GLE_KEY_F14 = GLFW_KEY_F14,
    GLE_KEY_F15 = GLFW_KEY_F15,
    GLE_KEY_F16 = GLFW_KEY_F16,
    GLE_KEY_F17 = GLFW_KEY_F17,
    GLE_KEY_F18 = GLFW_KEY_F18,
    GLE_KEY_F19 = GLFW_KEY_F19,
    GLE_KEY_F20 = GLFW_KEY_F20,
    GLE_KEY_F21 = GLFW_KEY_F21,
    GLE_KEY_F22 = GLFW_KEY_F22,
    GLE_KEY_F23 = GLFW_KEY_F23,
    GLE_KEY_F24 = GLFW_KEY_F24,
    GLE_KEY_F25 = GLFW_KEY_F25,
    GLE_KEY_KP_0 = GLFW_KEY_KP_0,
    GLE_KEY_KP_1 = GLFW_KEY_KP_0,
    GLE_KEY_KP_2 = GLFW_KEY_KP_2,
    GLE_KEY_KP_3 = GLFW_KEY_KP_3,
    GLE_KEY_KP_4 = GLFW_KEY_KP_4,
    GLE_KEY_KP_5 = GLFW_KEY_KP_5,
    GLE_KEY_KP_6 = GLFW_KEY_KP_6,
    GLE_KEY_KP_7 = GLFW_KEY_KP_7,
    GLE_KEY_KP_8 = GLFW_KEY_KP_8,
    GLE_KEY_KP_9 = GLFW_KEY_KP_9,
    GLE_KEY_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
    GLE_KEY_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
    GLE_KEY_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
    GLE_KEY_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
    GLE_KEY_KP_ADD = GLFW_KEY_KP_ADD,
    GLE_KEY_KP_ENTER = GLFW_KEY_KP_ENTER,
    GLE_KEY_KP_EQUAL = GLFW_KEY_KP_EQUAL,
    GLE_KEY_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
    GLE_KEY_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
    GLE_KEY_LEFT_ALT = GLFW_KEY_LEFT_ALT,
    GLE_KEY_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
    GLE_KEY_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
    GLE_KEY_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
    GLE_KEY_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
    GLE_KEY_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
    GLE_KEY_MENU = GLFW_KEY_MENU,
};

typedef void (*GLEkeyfun)(GLFWwindow *, int, int, int, int);
typedef void (*GLEcharfun)(GLFWwindow *, unsigned int);

bool KeyPressed(GLFWwindow *window, const GLEkey &key);
bool KeyHeld(GLFWwindow *window, const GLEkey &key);
bool KeyReleased(GLFWwindow *window, const GLEkey &key);

/* Sets the key callback for a specific window. Note that polling KeyPressed for this window will be unaffected. */
void SetKeyCallback(GLFWwindow *window, GLEkeyfun callback);
void SetNoKeyCallback(GLFWwindow *window);

/* Sets the char callback for a specific window. */
void SetCharCallback(GLFWwindow *window, GLEcharfun callback);
void SetNoCharCallback(GLFWwindow *window);

int GetScancodeFromKey(const GLEkey &key);
const char *GetLocalizedKeyName(const GLEkey &key);

/* --- Mouse --- */
enum GLEmousebutton
{
    GLE_MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_1,
    GLE_MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_2,
    GLE_MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_3,
    GLE_MOUSE_BUTTON_4 = GLFW_MOUSE_BUTTON_4,
    GLE_MOUSE_BUTTON_5 = GLFW_MOUSE_BUTTON_5,
    GLE_MOUSE_BUTTON_6 = GLFW_MOUSE_BUTTON_6,
    GLE_MOUSE_BUTTON_7 = GLFW_MOUSE_BUTTON_7,
    GLE_MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_8,
    GLE_MOUSE_BUTTON_LEFT = GLFW_MOUSE_BUTTON_LEFT,
    GLE_MOUSE_BUTTON_RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
    GLE_MOUSE_BUTTON_MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE
};

enum GLEcursormode
{
    GLE_CURSOR_MODE_NORMAL,
    GLE_CURSOR_MODE_WRAP,
    GLE_CURSOR_MODE_HIDDEN
};

typedef void (*GLEmousebuttonfun)(GLFWwindow *, int, int, int);
typedef void (*GLEcursorposfun)(GLFWwindow *, double, double);
typedef void (*GLEcursorenterfun)(GLFWwindow *, int);
typedef void (*GLEscrollfun)(GLFWwindow *, double, double);
typedef void (*GLEdropfun)(GLFWwindow *, int, const char **);

/* GLE_CURSOR_MODE_WRAP: Uses GLFW's disabled cursor mode, will hide the cursor and lock it to the center of the window */
/* TODO: Test what this returns when polling mouse pos (same as callback btw), either mouse pos that isn't limited to the window size or mouse pos delta of last frame */

/* GLE_CURSOR_MODE_NORMAL: Normal mode, GLE_CURSOR_MODE_HIDDEN: Hides the mouse but everything else acts the same */
void SetCursorMode(GLFWwindow *window, const GLEcursormode &cursorMode);
bool UseRawMouseMotion(GLFWwindow *window);     // returns false if the current system doesn't support raw mouse motion
bool DontUseRawMouseMotion(GLFWwindow *window); // returns false if the current system doesn't support raw mouse motion

glm::vec3 GetCursorPosition(GLFWwindow *window);
void SetCursorPosition(GLFWwindow *window, const glm::vec3 &pos);

bool MouseButtonPressed(GLFWwindow *window, const GLEmousebutton &mouseButton);
bool MouseButtonReleased(GLFWwindow *window, const GLEmousebutton &mouseButton);

void SetMouseButtonCallback(GLFWwindow *window, GLEmousebuttonfun callback);
void SetCursorPosCallback(GLFWwindow *window, GLEcursorposfun callback);
void SetCursorEnterCallback(GLFWwindow *window, GLEcursorenterfun callback);
void SetScrollCallback(GLFWwindow *window, GLEscrollfun callback);
void SetDropCallback(GLFWwindow *window, GLEdropfun callback);

/* --- Misc --- */
const char *GetClipboard();
void SetClipboard(const char *str);

} // namespace GLEngine

#endif