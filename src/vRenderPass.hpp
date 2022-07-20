#pragma once


#include "vDevice.hpp"
#include "vSwapChain.hpp"

class vRenderPass {
public:
    void init(vDevice *device, vSwapChain *swapChain);
    void destroy(vDevice *device);
    VkRenderPass getVKrenderPass();
private:
    VkRenderPass m_renderPass;
};