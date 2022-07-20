cmake_minimum_required(VERSION 3.23.2)
project(Kiwano VERSION 1.0.0)

add_library(kiwano src/DebugMessenger.cpp src/kiwano.cpp src/Renderer.cpp src/Util.cpp src/vClock.cpp src/vCommandBuffer.cpp src/vCommandPool.cpp src/vDevice.cpp src/vInstance.cpp src/vPipeLine.cpp src/vRenderPass.cpp src/vSurface.cpp src/vSwapChain.cpp src/vVertex.cpp src/Window.cpp)

set(CXX_STANDARD 17)

find_path(ourGLMLib glm NAMES glm GLM DOC "OpenGL Mathematics Library")
find_library(ourGLFWLib glfw NAMES glfw glfw3 GLFW GLFW3 DOC "Windowing Library")
find_path(ourGLFWinclude glfw NAMES glfw GLFW3 GLFW GLFW3 DOC "Include directory for glfw")
find_library(ourVulkanLib vulkan NAMES Vulkan VULKAN vulkan DOC "Vulkan dynamic library sdk")
find_path(ourVulkanInclude vulkan)

target_include_directories(kiwano PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/Kiwano)
target_include_directories(kiwano PUBLIC ${ourGLFWinclude})
target_include_directories(kiwano PUBLIC ${ourGLMLib})
target_include_directories(kiwano PUBLIC ${ourVulkanInclude})
target_link_libraries(kiwano PRIVATE ${ourGLFWLib})
target_link_libraries(kiwano PRIVATE ${ourVulkanLib})

