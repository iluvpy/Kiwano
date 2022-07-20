#include "vCommandBuffer.hpp"


void vCommandBuffer::init(vDevice *device, vRenderPass *renderPass, vSwapChain *swapChain, vCommandPool *commandPool, vPipeLine *pipeLine)  
{
    m_renderPass = renderPass;
    m_swapChain = swapChain;
    m_pipeLine = pipeLine;

    m_commandBuffers.resize(RenderConfig::MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool->getVKcommandPool();
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t) m_commandBuffers.size();

    if (vkAllocateCommandBuffers(device->getVKdevice(), &allocInfo, m_commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void vCommandBuffer::reset(vClock *clock) {
    vkResetCommandBuffer(m_commandBuffers[clock->getCurrentFrame()], 0);
}

VkCommandBuffer vCommandBuffer::getCommandBuffer(vClock *clock) {
    return m_commandBuffers[clock->getCurrentFrame()];
}

VkCommandBuffer *vCommandBuffer::getCommandBufferPtr(vClock *clock) {
    return &m_commandBuffers[clock->getCurrentFrame()];
}

void vCommandBuffer::record(uint32_t currentFrame, uint32_t imageIndex, vVertex *vertex) {
    VkCommandBuffer commandBuffer = m_commandBuffers[currentFrame];
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = m_renderPass->getVKrenderPass();
    renderPassInfo.framebuffer = m_swapChain->getFrameBuffer(imageIndex);
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = m_swapChain->getExtent();

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeLine->getVKpipeLine());

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float) m_swapChain->getExtent().width;
        viewport.height = (float) m_swapChain->getExtent().height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = m_swapChain->getExtent();
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_pipeLine->getVKpipeLine());

        VkBuffer vertexBuffers[] = {vertex->getVKbuffer()};
        VkDeviceSize offsets[] = {0};
        vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

        vkCmdDraw(commandBuffer, vertex->getNumberOfVertices(), 1, 0, 0);

    vkCmdEndRenderPass(commandBuffer);

    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

