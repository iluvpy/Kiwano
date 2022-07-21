#pragma once

#include <stdexcept>
#include <vulkan/vulkan.h>
#include "preDef.hpp"

class vRenderPass {
public:
    void init(vDevice *device, vSwapChain *swapChain);
    void destroy(vDevice *device);
    VkRenderPass getVKrenderPass();
private:
    VkRenderPass m_renderPass;
};