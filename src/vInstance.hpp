#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <cstring>

class vInstance {
public:
    void init();
    bool checkValidationLayerSupport();
    VkInstance getVKinstance();
    void destroy();
private:
    VkInstance m_instance;

};