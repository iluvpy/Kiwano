#include "DebugMessenger.hpp"


void DebugMessenger::init(vInstance *instance) {
    if (!RenderConfig::enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(instance->getVKinstance(), &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void DebugMessenger::destroy(vInstance *instance) {
    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(instance->getVKinstance()., m_debugMessenger, nullptr);
    }
}