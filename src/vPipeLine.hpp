#pragma once

#include "vDevice.hpp"
#include "Vertex.hpp"
#include "vRenderPass.hpp"

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