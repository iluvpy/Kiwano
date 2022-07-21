#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "preDef.hpp"

class vPipeLine {
public:
    void init(vDevice *device, vRenderPass *renderPass);
    void destroy(vDevice *device);
    VkPipeline getVKpipeLine();
private:

    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_graphicsPipeline;

    VkShaderModule createShaderModule(vDevice *device, const std::vector<char>& code);
};