#pragma once

#include <vulkan/vulkan.h>
#include "preDef.hpp"

class DebugMessenger {
public:
    void init(vInstance *instance);
    void destroy(vInstance *instance);
private:
    VkDebugUtilsMessengerEXT m_debugMessenger;
};