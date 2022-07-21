#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "preDef.hpp"

class vCommandBuffer {
public:
    void init(vDevice *device, vRenderPass *renderPass, vSwapChain *swapChain, vCommandPool *commandPool, vPipeLine *pipeLine);
    void record(uint32_t currentFrame, uint32_t imageIndex, vVertex *vertex);
    void reset(vClock *clock);
    VkCommandBuffer getCommandBuffer(vClock *clock);
    VkCommandBuffer *getCommandBufferPtr(vClock *clock);
    
private:
    std::vector<VkCommandBuffer> m_commandBuffers;
    vRenderPass *m_renderPass;
    vSwapChain *m_swapChain;
    vPipeLine *m_pipeLine;
};