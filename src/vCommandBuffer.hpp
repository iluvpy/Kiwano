#pragma once

#include "vDevice.hpp"
#include "vRenderPass.hpp"
#include "vCommandPool.hpp"
#include "vClock.hpp"
#include "vVertex.hpp"
#include "vPipeLine.hpp"

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