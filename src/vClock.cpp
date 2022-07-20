#include "vClock.hpp"



void vClock::init(vDevice *device) {
    m_imageAvailableSemaphores.resize(RenderConfig::MAX_FRAMES_IN_FLIGHT);
    m_renderFinishedSemaphores.resize(RenderConfig::MAX_FRAMES_IN_FLIGHT);
    m_inFlightFences.resize(RenderConfig::MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < RenderConfig::MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(device->getVKdevice(), &semaphoreInfo, nullptr, &m_imageAvailableSemaphores[i]) != VK_SUCCESS ||
            vkCreateSemaphore(device->getVKdevice(), &semaphoreInfo, nullptr, &m_renderFinishedSemaphores[i]) != VK_SUCCESS ||
            vkCreateFence(device->getVKdevice(), &fenceInfo, nullptr, &m_inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
}

void vClock::destroy(vDevice *device) {
    for (size_t i = 0; i < RenderConfig::MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(device->getVKdevice(), m_renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(device->getVKdevice(), m_imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(device->getVKdevice(), m_inFlightFences[i], nullptr);
    }
}


void vClock::waitForLastFrame(vDevice *device) {
    vkWaitForFences(device->getVKdevice(), 1, &m_inFlightFences[m_currentFrame], VK_TRUE, UINT64_MAX);
}

uint32_t vClock::getCurrentFrame() {
    return m_currentFrame;
}

void vClock::reset(vDevice *device) {
    vkResetFences(device->getVKdevice(), 1, &m_inFlightFences[m_currentFrame]);
}

void vClock::update() {
    m_currentFrame = (m_currentFrame + 1) % RenderConfig::MAX_FRAMES_IN_FLIGHT;
}

VkSemaphore vClock::getAvailableImageSemaphore() {
    return m_imageAvailableSemaphores[m_currentFrame];
}
VkSemaphore vClock::getRenderFinishedSemaphore() {
    return m_renderFinishedSemaphores[m_currentFrame];
}

VkFence vClock::getInflightFence() {
    return m_inFlightFences[m_currentFrame];
}

