#pragma once

#include "vInstance.hpp"
#include "RenderConfig.hpp"
#include "Util.hpp"

class DebugMessenger {
public:
    void init(vInstance *instance);
    void destroy(vInstance *instance);
private:
    VkDebugUtilsMessengerEXT m_debugMessenger;
};