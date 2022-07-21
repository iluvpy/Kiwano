#pragma once

#include <vulkan/vulkan.h>
#include "preDef.hpp"

class vCommandPool {
public:
    void init(vDevice *device, vSurface *surface);
    void destroy(vDevice *device);
    VkCommandPool getVKcommandPool();
private:
    VkCommandPool m_commandPool;

};