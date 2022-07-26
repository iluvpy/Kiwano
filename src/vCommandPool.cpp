#include "vCommandPool.hpp"


void vCommandPool::init(vDevice *device) {
    QueueFamilyIndices queueFamilyIndices = Util::findQueueFamilies(device->getVkphysicalDevice());

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(device->getVKdevice(), &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}


void vCommandPool::destroy(vDevice *device) {
    vkDestroyCommandPool(device->getVKdevice(), m_commandPool, nullptr);
}


VkCommandPool vCommandPool::getVkcommandPool() {
    return m_commandPool;
}
