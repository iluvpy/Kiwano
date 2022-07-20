#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>


#include "Window.hpp"
#include "vInstance.hpp"

class vSurface {
public:
    void init(vInstance *instance, Window *window);
    void destroy(vInstance *instance);
    VkSurfaceKHR getVKsurface();

private:

    VkSurfaceKHR m_surface;
    

}