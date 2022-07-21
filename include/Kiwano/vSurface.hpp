#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

#include "preDef.hpp"

class vSurface {
public:
    void init(vInstance *instance, Window *window);
    void destroy(vInstance *instance);
    VkSurfaceKHR getVKsurface();

private:

    VkSurfaceKHR m_surface;
    
};