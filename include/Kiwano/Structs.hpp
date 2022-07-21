#pragma once

#include <vulkan/vulkan.h>
#include <optional>
#include <vector>

/**
 * for vscode users: 
 *  right now the vscode linter cannot find std::optional,
 *  for now just ignore it and do not disable "error squiggles"
 *  as that will disable them for the whole project. 
 */
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};