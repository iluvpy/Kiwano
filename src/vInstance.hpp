#pragma once

#include <vulkan/vulkan.h>
#include <stdexcept>
#include <cstring>
#include "RenderConfig.hpp"
#include "Util.hpp"

class vInstance {
public:
    void init();
    bool checkValidationLayerSupport();
    VkInstance getVKinstance();
    void destroy();
private:
    VkInstance m_instance;

};