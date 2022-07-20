#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <set>

#include "RenderConfig.hpp"
#include "vInstance.hpp"
#include "DebugMessenger.hpp"
#include "Window.hpp"
#include "vSurface.hpp"
#include "vDevice.hpp"
#include "vSwapChain.hpp"
#include "vRenderPass.hpp"
#include "vPipeLine.hpp"
#include "vCommandPool.hpp"
#include "vCommandBuffer.hpp"
#include "vVertex.hpp"
#include "vClock.hpp"


class Renderer {
public:
    void init();
    void destroy();
    void drawFrame();
private:

    Window m_window;
    vInstance m_instance;
    DebugMessenger m_debugMessenger;
    vSurface m_surface;
    vDevice m_device;

    vSwapChain m_swapChain;
    vRenderPass m_renderPass;

    vPipeLine m_pipeLine;
    vCommandPool m_commandPool;

    vVertex m_vertex;
    vCommandBuffer m_commandBuffer;

    vClock m_clock;


    //bool framebufferResized = false;

    // static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    //     auto app = reinterpret_cast<Renderer*>(glfwGetWindowUserPointer(m_window.getWindowPtr()));
    //     app->framebufferResized = true;
    // }
    void setPresent();

};
