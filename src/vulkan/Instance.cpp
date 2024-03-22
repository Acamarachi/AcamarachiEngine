#include <iostream>
#include "Instance.hpp"
#include "Utils.hpp"

static VkBool32 debugMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT *data, void *userdata)
{
    (void)userdata;
    std::cout << "Validation layer(" << severity << " :: " << string_VkDebugUtilsMessageTypeFlagsEXT(type) << "): " << data->pMessage << std::endl;
    return VK_FALSE;
}

Acamarachi::Vulkan::Instance::Error Acamarachi::Vulkan::Instance::initialize(const char *appName, std::vector<const char *> requiredExtensions, std::vector<const char *> requiredValidationLayers)
{
    Acamarachi::Vulkan::Instance instance;

    VkApplicationInfo applicationInfo = {};
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    applicationInfo.pNext = 0;
    applicationInfo.pApplicationName = appName;
    applicationInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    applicationInfo.pEngineName = "Acamarachi Engine";
    applicationInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    applicationInfo.apiVersion = VK_API_VERSION_1_3;

    VkInstanceCreateInfo instanceCreateInfo = {};
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = 0;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &applicationInfo;
    instanceCreateInfo.enabledLayerCount = (uint32_t)requiredValidationLayers.size();
    instanceCreateInfo.ppEnabledLayerNames = requiredValidationLayers.data();
    instanceCreateInfo.enabledExtensionCount = (uint32_t)requiredExtensions.size();
    instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();

    VkResult result = vkCreateInstance(&instanceCreateInfo, 0, &instance.handle);
    if (result != VK_SUCCESS)
    {
        std::cerr << "Failed to initialized instance with error: " << Acamarachi::Vulkan::vkErrorToString(result) << std::endl;
        return Acamarachi::Vulkan::VkResultToVulkanError(result);
    }

    if (requiredValidationLayers.size() != 0)
    {
        // VK_EXT_debug_utils allow more debug information to the user
        // for more info see : https://registry.khronos.org/vulkan/specs/1.3-extensions/man/html/VK_EXT_debug_utils.html

        PFN_vkCreateDebugUtilsMessengerEXT fn = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance.handle, "vkCreateDebugUtilsMessengerEXT");
        VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo = {};
        debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugMessengerCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                                                   VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
                                                   VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                                                   VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugMessengerCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                               VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                               VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugMessengerCreateInfo.pfnUserCallback = &debugMessengerCallback;

        fn(instance.handle, &debugMessengerCreateInfo, 0, &instance.debugMessenger);
    }
    return instance;
}

void Acamarachi::Vulkan::Instance::deinitialize()
{
    if (this->debugMessenger != VK_NULL_HANDLE)
    {
        PFN_vkDestroyDebugUtilsMessengerEXT fn = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(handle, "vkDestroyDebugUtilsMessengerEXT");
        fn(handle, debugMessenger, 0);
    }
    vkDestroyInstance(handle, 0);
    handle = VK_NULL_HANDLE;
}

bool Acamarachi::Vulkan::Instance::getAvailablePhysicalDevices(std::vector<VkPhysicalDevice>& physicalDevices)
{
    // Get the number of physical devices
    uint32_t count = 0;
    VkResult res = vkEnumeratePhysicalDevices(this->handle, &count, 0);
    if (res != VK_SUCCESS) {
        return false;
    }

    physicalDevices.resize(count);

    // Get the actuals physcial devices
    res = vkEnumeratePhysicalDevices(this->handle, &count, physicalDevices.data());
    if (res != VK_SUCCESS) {
        return false;
    }
    return true;
}