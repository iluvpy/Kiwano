#include "Window.hpp"


void Window::init() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    m_window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void Window::destroy() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}


bool Window::windowOpen() {
    return !glfwWindowShouldClose(m_window);
}


GLFWwindow *Window::getGLFWwindow() {
    return m_window;
}