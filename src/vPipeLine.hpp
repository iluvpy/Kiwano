#pragma once

#include "vDevice.hpp"
#include "Vertex.hpp"

class vPipeLine {
public:
    void init(vDevice *device);
    void destroy(vDevice *device);
private:

    VkPipelineLayout m_pipelineLayout;
    VkPipeline m_graphicsPipeline;

    VkShaderModule createShaderModule(vDevice *device, const std::vector<char>& code);

}