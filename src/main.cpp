#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>

#include "vulkan/Instance.hpp"
#include "vulkan/Device.hpp"
#include "vulkan/Surface.hpp"
#include "vulkan/Swapchain.hpp"
#include "vulkan/FrameInformation.hpp"

void error_callback(int error, const char *description)
{
    std::cerr << "Error" << error << ": " << description << "\n"
              << std::endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    (void)scancode;
    (void)mods;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return 1;
    }

    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow *window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to initialize GLFW Window" << std::endl;
        return 1;
    }
    glfwSetKeyCallback(window, key_callback);

    std::vector<const char *> instance_layers;
    std::vector<const char *> instance_extensions;
    std::vector<const char *> device_extensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    instance_layers.push_back("VK_LAYER_KHRONOS_validation");

    instance_extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    uint32_t count = 0;
    const char **glfw_required_extensions = glfwGetRequiredInstanceExtensions(&count);
    for (uint32_t i = 0; i < count; i++)
    {
        instance_extensions.push_back(glfw_required_extensions[i]);
    }

    Acamarachi::Vulkan::Instance instance = Acamarachi::Vulkan::Instance();
    if (!instance.initialize("Test", instance_extensions, instance_layers))
    {
        std::cerr << "Failed to create instance" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    Acamarachi::Vulkan::Surface surface = Acamarachi::Vulkan::Surface();
    if (!surface.initialize(instance, window, reinterpret_cast<Acamarachi::Vulkan::CreateWindowSurfaceFunction *>(glfwCreateWindowSurface)))
    {
        std::cerr << "Failed to create surface" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    Acamarachi::Vulkan::Device device = Acamarachi::Vulkan::Device();
    if (!device.initialize(instance, surface, device_extensions, instance_layers))
    {
        std::cerr << "Failed to create device" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    Acamarachi::Vulkan::Swapchain swapchain = Acamarachi::Vulkan::Swapchain();
    if (!swapchain.initialize(device, surface, 1280, 720))
    {
        std::cerr << "Failed to create swapchain" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    Acamarachi::Vulkan::FrameInformation frameInformation = Acamarachi::Vulkan::FrameInformation();
    if (!frameInformation.initialize(device))
    {
        std::cerr << "Failed to create frame information" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        (void)frameInformation.draw(device, swapchain);
    }

    vkDeviceWaitIdle(device.handle);
    frameInformation.deinitialize(device);
    swapchain.deinitialize(device);
    device.deinitialize();
    surface.deinitialize(instance);
    //instance.deinitialize();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}