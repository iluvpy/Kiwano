#pragma once

#include <cstring>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include <vector>
#include "preDef.hpp"

class vVertex {
public:
    void init(vDevice *device, std::vector<Vertex> vertices, vCommandPool *commandPool);
    void destroy(vDevice *device);
    VkBuffer getVKbuffer();
    uint32_t getNumberOfVertices();
private:
    VkBuffer m_vertexBuffer;
    VkDeviceMemory m_vertexBufferMemory;
    uint32_t m_numberOfVertices;

    void createBuffer(vDevice *device,
                      VkDeviceSize size, 
                      VkBufferUsageFlags usage, 
                      VkMemoryPropertyFlags properties, 
                      VkBuffer& buffer, 
                      VkDeviceMemory& bufferMemory);
    void copyBuffer(vDevice *device,
                    vCommandPool *commandPool,
                    VkBuffer srcBuffer, 
                    VkBuffer dstBuffer, 
                    VkDeviceSize size);

    uint32_t findMemoryType(vDevice *device, uint32_t typeFilter, VkMemoryPropertyFlags properties);
};