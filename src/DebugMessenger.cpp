#include "DebugMessenger.hpp"
#include "vInstance.hpp"
#include "RenderConfig.hpp"
#include "Util.hpp"

void DebugMessenger::init(vInstance *instance) {
    if (!RenderConfig::enableValidationLayers) return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    Util::populateDebugMessengerCreateInfo(createInfo);

    if (Util::CreateDebugUtilsMessengerEXT(instance->getVKinstance(), &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
}

void DebugMessenger::destroy(vInstance *instance) {
    if (RenderConfig::enableValidationLayers) {
        Util::DestroyDebugUtilsMessengerEXT(instance->getVKinstance(), m_debugMessenger, nullptr);
    }
}