#pragma once

#include "vDevice.hpp"
#include "vRenderPass.hpp"
#include "vCommandPool.hpp"
#include "vClock.hpp"

class vCommandBuffer {
public:
    void init(vDevice *device, vRenderPass *renderPass, vSwapChain *swapChain, vCommandPool *commandPool);
    void record(uint32_t currentFrame, uint32_t imageIndex);
    void reset();
    VkCommandBuffer getCommandBuffer(vClock *clock);
private:
    std::vector<VkCommandBuffer> m_commandBuffers;
    vRenderPass *m_renderPass;
    vSwapChain *m_swapChain;
}