#ifndef ACAMARACHI_VULKAN_CONTEXT
#define ACAMARACHI_VULKAN_CONTEXT 1

#include <vulkan/vulkan.h>

#include "Instance.hpp"
#include "Surface.hpp"
#include "Device.hpp"
#include "Swapchain.hpp"
#include "FrameInformation.hpp"

namespace Acamarachi::Vulkan
{
    using CreateWindowSurfaceFunction = VkResult (VkInstance instance, void* window, const VkAllocationCallbacks* callbacks, VkSurfaceKHR *surface);
    using GetRequiredExtensions = const char ** (uint32_t *);

    class Context
    {
    public:
        Instance instance;
        Surface surface;
        Device device;
        Swapchain swapchain;
        FrameInformation frameInfo;

        Context() = default;
        Context(const Context&) = delete;

        ~Context() = default;

        bool initialize(const char *appName, GetRequiredExtensions* getRequiredExtensions, void* window, CreateWindowSurfaceFunction *createWindowSurface);
        void deinitialize();

    };
}

#endif