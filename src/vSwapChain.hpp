#pragma once

#include <vulkan/vulkan.h>
#include "vDevice.hpp"
#include "vSurface.hpp"
#include "Window.hpp"
#include "vRenderPass.hpp"

class vSwapChain {
public:
    void init(vDevice *device, vSurface *surface, Window *window);
    void destroy(vDevice *device);
    void createFramebuffers(vDevice *device, vRenderPass *renderpass);
    VkFormat getFormat();
    VkExtent2D getExtent();
    VkSwapchainKHR getVKswapChain();
private:

    VkSwapchainKHR m_swapChain;
    std::vector<VkImage> m_swapChainImages;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;
    std::vector<VkImageView> m_swapChainImageViews;
    std::vector<VkFramebuffer> m_swapChainFramebuffers;


    SwapChainSupportDetails vSwapChain::querySwapChainSupport(vDevice *device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, Window *window);

    void createImageViews(vDevice *device);
    void createSwapChain(vDevice *device, vSurface *surface, Window *window);

}