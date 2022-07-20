#include "Renderer.hpp"


const std::vector<Vertex> vertices = {
    {{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
    {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

void Renderer::init() {
    m_window.init();
    m_instance.init();
    m_debugMessenger.init(&m_instance);
    m_surface.init(&m_instance, &m_window);
    m_device.init(&m_instance);
    m_swapChain.init(&m_device, &m_surface, &m_window);
    m_renderPass.init(&m_device, &m_swapChain);
    m_swapChain.createFramebuffers(&m_device, &m_renderPass);
    m_commandPool.init(&m_device);
    m_vertex.init(&m_device, vertices);
    m_commandBuffer.init(&m_device, &m_renderPass, &m_swapChain, &m_commandPool);
    m_clock.init(&m_device);
}



void Renderer::drawFrame() {
    m_clock.waitForLastFrame();

    uint32_t imageIndex;
    vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

    m_clock.reset(&m_device);

    m_commandBuffer.reset();
    m_commandBuffer.record(currentFrame, imageIndex);

    setPresent();

    m_clock.update();
}

void Renderer::setPresent() {
    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {m_clock.getAvailableImageSemaphore()};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = m_commandBuffer.getCommandBuffer(&m_clock);

    VkSemaphore signalSemaphores[] = {m_clock.getRenderFinishedSemaphore()};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (vkQueueSubmit(m_device.getGraphicsQueue(), 1, &submitInfo, m_clock.getInflightFence()) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {m_swapChain.getVKswapChain()};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = m_swapChains;

    presentInfo.pImageIndices = &imageIndex;

    vkQueuePresentKHR(m_device.getPresentQueue(), &presentInfo);
}




void Renderer::destroy() {
    m_swapChain.destroy(&m_device);


    m_pipeLine.destroy(&m_device);
    m_renderPass.destroy(&m_device);
    m_vertex.destroy(&m_device);

    m_clock.destroy(&m_device);

    m_commandPool.destroy(&m_device);

    m_debugMessenger.destroy(&m_instance);

    m_surface.destroy();
    m_instance.destroy();
    m_window.destroy();
}
