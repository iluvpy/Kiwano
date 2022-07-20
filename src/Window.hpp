#pragma once

#include <GLFW/glfw3.h>

class Window {
public:

    static const int WIDTH = 800;
    static const int HEIGHT = 600;

    void init();
    void destroy();
    bool windowOpen();
    GLFWwindow *getGLFWwindow();

private:

    GLFWwindow *m_window;

};