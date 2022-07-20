#pragma once

#include <vulkan/vulkan.h>
#include <set>
#include <vector>
#include <string>
#include "preDef.hpp"

class vDevice {
public:
    void init(vInstance *instance, vSurface *surface);
    void destroy();
    VkDevice getVKdevice();
    VkPhysicalDevice getVKphysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device, vSurface *surface);
    VkQueue getGraphicsQueue();
    VkQueue getPresentQueue();

private:
    VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
    VkDevice m_device;
    VkQueue m_graphicsQueue;
    VkQueue m_presentQueue;
    
    void pickPhysicalDevice(vInstance *instance, vSurface *surface);
    void createLogicalDevice(vSurface *surface);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

};