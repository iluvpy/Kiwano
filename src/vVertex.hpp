#pragma once

#include <cstring>
#include "vDevice.hpp"
#include "Vertex.hpp"
#include "vCommandPool.hpp"

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

    uint32_t findMemoryType(vDevice *device, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(device->getVKphysicalDevice(), &memProperties);
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

};