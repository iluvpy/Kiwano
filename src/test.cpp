#include <iostream>
#include "Window.hpp"
#include "Renderer.hpp"
// testing kiwano

int main() {
    Window window;
    window.init();
    Renderer renderer;
    renderer.init(&window);

    while (window.windowOpen()) {
        window.pollEvents();
        renderer.drawFrame();
    }
}