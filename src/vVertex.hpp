#pragma once

#include "vDevice.hpp"
#include "Vertex.hpp"

class vVertex {
public:
    void init(vDevice *device, std::vector<Vertex> vertices);
    void destroy(vDevice *device);
    
private:
    VkBuffer m_vertexBuffer;
    VkDeviceMemory m_vertexBufferMemory;

    void createBuffer(vDevice *device,
                      VkDeviceSize size, 
                      VkBufferUsageFlags usage, 
                      VkMemoryPropertyFlags properties, 
                      VkBuffer& buffer, 
                      VkDeviceMemory& bufferMemory);
    void copyBuffer(vDevice *device,
                    VkBuffer srcBuffer, 
                    VkBuffer dstBuffer, 
                    VkDeviceSize size);

    uint32_t findMemoryType(vDevice *device, uint32_t typeFilter, VkMemoryPropertyFlags properties) {
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &memProperties);
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

}