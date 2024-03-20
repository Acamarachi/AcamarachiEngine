#ifndef ACAMARACHI_VULKAN_ALLOCATOR
#define ACAMARACHI_VULKAN_ALLOCATOR 1

#include "Device.hpp"

namespace Acamarachi::Vulkan
{
    struct DeviceAllocation {
        VkDeviceMemory memory;
        VkDeviceSize size;
        VkDeviceSize offset;
        bool free;
        void *mapped_ptr = nullptr;

        bool operator==(DeviceAllocation const&);
    };

    class DeviceMemoryChunk {
    public:
        DeviceMemoryChunk(Device& device, VkDeviceSize size, uint32_t memoryTypeIndex);

        bool alloc(Device& device, VkDeviceSize size, VkDeviceSize alignment, DeviceAllocation& allocation);
        bool ownsAllocation(DeviceAllocation& allocation);
        void dealloc(DeviceAllocation const& allocation);
        uint32_t getMemoryTypeIndex();
    private:
        uint32_t memoryTypeIndex;
        VkDeviceMemory memory = VK_NULL_HANDLE;
        VkDeviceSize size;
        std::vector<DeviceAllocation> allocations;
        void *mapped_ptr = nullptr;
    };

    class DeviceAllocator {
    private:
        Device& device;
        VkDeviceSize pageSize;

    public:
        DeviceAllocator(Device& device);
        ~DeviceAllocator();

        // https://registry.khronos.org/vulkan/specs/1.0/html/vkspec.html#memory-device
        uint32_t findMemoryProperties(const VkPhysicalDeviceMemoryProperties* pMemoryProperties, uint32_t memoryTypeBitsRequirement, VkMemoryPropertyFlags requiredProperties);
    };
}

#endif