#pragma once

#include "vInstance.hpp"
#include "RenderConfig.hpp"

class DebugMessenger {
    void init(vInstance *instance);
    void destroy(vInstance *instance);
private:
    VkDebugUtilsMessengerEXT m_debugMessenger;
}