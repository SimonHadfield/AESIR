#include "Window.h"

namespace Hana {

    Window::Window() {}
    Window::~Window() {}

    void* Window::InitWindow()
    {
        glfwInit();

        // Initialize GLFW and create a window.
        if (glfwInit()) {
            m_Window = glfwCreateWindow(800, 600, "My Window", nullptr, nullptr);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        return m_Window;
    }
}