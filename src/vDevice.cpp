#include "vDevice.hpp"
#include "Structs.hpp"
#include "RenderConfig.hpp"
#include "Util.hpp"
#include "vInstance.hpp"
#include "vSurface.hpp"


void vDevice::init(vInstance *instance, vSurface *surface)  {
    pickPhysicalDevice(instance, surface);
    createLogicalDevice(surface);
}

void vDevice::pickPhysicalDevice(vInstance *instance, vSurface *surface) {
    // picks a gpu with vulkan support and the correct extensions
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance->getVKinstance(), &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
    }
 
    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance->getVKinstance(), &deviceCount, devices.data());

    for (const auto& device : devices) {
        if (isDeviceSuitable(device, surface)) {
            m_physicalDevice = device;
            break;
        }
    }

    if (m_physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("failed to find a suitable GPU!");
    }
}

void vDevice::createLogicalDevice(vSurface *surface) {
    QueueFamilyIndices indices = Util::findQueueFamilies(m_physicalDevice, surface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    float queuePriority = 1.0f;
    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(RenderConfig::deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = RenderConfig::deviceExtensions.data();

    if (RenderConfig::enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(RenderConfig::validationLayers.size());
        createInfo.ppEnabledLayerNames = RenderConfig::validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    vkGetDeviceQueue(m_device, indices.graphicsFamily.value(), 0, &m_graphicsQueue);
    vkGetDeviceQueue(m_device, indices.presentFamily.value(), 0, &m_presentQueue);
}


void vDevice::destroy() {
    vkDestroyDevice(m_device, nullptr);
}


bool vDevice::isDeviceSuitable(VkPhysicalDevice device, vSurface *surface) {
    QueueFamilyIndices indices = Util::findQueueFamilies(device, surface);

    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = Util::querySwapChainSupport(device, surface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}


bool vDevice::checkDeviceExtensionSupport(VkPhysicalDevice device) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(RenderConfig::deviceExtensions.begin(), RenderConfig::deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}


VkDevice vDevice::getVKdevice() {
    return m_device;
}

VkPhysicalDevice vDevice::getVKphysicalDevice() {
    return m_physicalDevice;
}

VkQueue vDevice::getGraphicsQueue() {
    return m_graphicsQueue;
}

VkQueue vDevice::getPresentQueue() {
    return m_presentQueue;
}