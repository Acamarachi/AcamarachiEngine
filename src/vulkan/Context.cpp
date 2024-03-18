#include <iostream>
#include "Context.hpp"

// TODO: Better error handling and reporting
bool Acamarachi::Vulkan::Context::initialize(const char *appName, GetRequiredExtensions *getRequiredExtensions, void *window, CreateWindowSurfaceFunction *createWindowSurface)
{

    std::vector<const char *> instance_layers;
    std::vector<const char *> instance_extensions;
    std::vector<const char *> device_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    instance_layers.push_back("VK_LAYER_KHRONOS_validation");

    instance_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    uint32_t count = 0;
    const char **glfw_required_extensions = getRequiredExtensions(&count);
    for (uint32_t i = 0; i < count; i++)
    {
        instance_extensions.push_back(glfw_required_extensions[i]);
    }

    instance = Acamarachi::Vulkan::Instance();
    if (!instance.initialize(appName, instance_extensions, instance_layers))
    {
        std::cerr << "Failed to create instance" << std::endl;
        return false;
    }

    surface = Acamarachi::Vulkan::Surface();
    if (!surface.initialize(instance, window, createWindowSurface)) // reinterpret_cast<Acamarachi::Vulkan::CreateWindowSurfaceFunction *>(glfwCreateWindowSurface)))
    {
        std::cerr << "Failed to create surface" << std::endl;
        return false;
    }

    device = Acamarachi::Vulkan::Device();
    if (!device.initialize(instance, surface, device_extensions, instance_layers))
    {
        std::cerr << "Failed to create device" << std::endl;
        return false;
    }

    swapchain = Acamarachi::Vulkan::Swapchain();
    if (!swapchain.initialize(device, surface, 1280, 720))
    {
        std::cerr << "Failed to create swapchain" << std::endl;
        return false;
    }

    frameInfo = Acamarachi::Vulkan::FrameInformation();
    if (!frameInfo.initialize(device))
    {
        std::cerr << "Failed to create frame information" << std::endl;
        return false;
    }

    return true;
}

void Acamarachi::Vulkan::Context::deinitialize()
{
    vkDeviceWaitIdle(device.handle);
    frameInfo.deinitialize(device);
    swapchain.deinitialize(device);
    device.deinitialize();
    surface.deinitialize(instance);
    instance.deinitialize();
}