#pragma once

#include "vDevice.hpp"

class vCommandPool {
public:
    void init(vDevice *device);
    void destroy(vDevice *device);
    VkCommandPool getVkcommandPool();
private:
    VkCommandPool m_commandPool;

}