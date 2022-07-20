#pragma once

#include <cstdlib>
#include <vector>
#include <cstdint>
#include <vulkan/vulkan.h>
#include "preDef.hpp"

class vClock {
public: 
    void init(vDevice *device);
    void destroy(vDevice *device);
    uint32_t getCurrentFrame();
    void waitForLastFrame(vDevice *device);
    void reset(vDevice *device);
    void update();
    VkSemaphore getAvailableImageSemaphore();
    VkSemaphore getRenderFinishedSemaphore();
    VkFence getInflightFence();
private:
    std::vector<VkSemaphore> m_imageAvailableSemaphores;
    std::vector<VkSemaphore> m_renderFinishedSemaphores;
    std::vector<VkFence> m_inFlightFences;
    uint32_t m_currentFrame = 0;

};