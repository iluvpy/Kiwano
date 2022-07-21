#pragma once

#include <vector>

namespace RenderConfig {
    
    #ifdef NDEBUG
    const bool enableValidationLayers = false;
    #else
    const bool enableValidationLayers = true;
    #endif

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    const std::string VertexShaderPath = "shaders/vert.spv";
    const std::string FragmentShaderPath = "shaders/frag.spv";
    const int MAX_FRAMES_IN_FLIGHT = 2;

}