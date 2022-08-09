#pragma once

#include <cstring>
#include <stdexcept>
#include <vulkan/vulkan.h>
#include <vector>
#include "preDef.hpp"

class vVertex {
public:
    void init(vDevice *device, std::vector<Vertex> vertices, std::vector<uint16_t> indices, vCommandPool *commandPool);
    void destroy(vDevice *device);
    VkBuffer getVertexVKbuffer();
    VkBuffer getIndeciesVKBuffer();
    uint32_t getNumberOfVertices();
    uint32_t getNumberOfIndecies();
private:
    VkBuffer m_vertexBuffer;
    VkDeviceMemory m_vertexBufferMemory;
    VkBuffer m_indexBuffer;
    VkDeviceMemory m_indexBufferMemory;
    uint32_t m_numberOfVertices;
    uint32_t m_numberOfIndecies;

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