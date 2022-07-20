#include "vSurface.hpp"


void vSurface::init(vInstance *instance, Window *window) {
    if (glfwCreateWindowSurface(instance->getVKinstance(), window->getGLFWwindow(), nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("failed to create window surface!");
    }
}

void vSurface::destroy(vInstance *instance) {
    vkDestroySurfaceKHR(instance->getVKinstance(), m_surface, nullptr);
}

VkSurfaceKHR vSurface::getVKsurface() {
    return m_surface;
}
