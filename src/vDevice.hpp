#pragma once

#include <vulkan/vulkan.h>
#include <set>
#include <vector>
#include "Structs.hpp"
#include "RenderConfig.hpp"
#include "Util.hpp"
#include "vInstance.hpp"

class vDevice {
public:
    void init(vInstance *instance);
    void destroy();
    VkDevice getVKdevice();
    VkPhysicalDevice getVkphysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    VkQueue getGraphicsQueue();
    VkQueue getPresentQueue();

private:
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device;
    VkQueue m_graphicsQueue;
    VkQueue m_presentQueue;
    

    void pickPhysicalDevice(vInstance *instance);
    void createLogicalDevice();

}