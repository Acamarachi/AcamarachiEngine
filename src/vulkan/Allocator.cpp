#include "Allocator.hpp"
#include <algorithm>

bool Acamarachi::Vulkan::DeviceAllocation::operator==(DeviceAllocation const &other)
{
    return (memory == other.memory && offset == other.offset && size == other.size && free == other.free && mapped_ptr == other.mapped_ptr);
}

Acamarachi::Vulkan::DeviceMemoryChunk::DeviceMemoryChunk(Device &device, VkDeviceSize chunkSize, uint32_t chunkMemoryTypeIndex)
    : size(chunkSize), memoryTypeIndex(chunkMemoryTypeIndex)
{
    VkMemoryAllocateInfo allocateInfo = {};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.memoryTypeIndex = memoryTypeIndex;
    allocateInfo.allocationSize = size;

    vkAllocateMemory(device.handle, &allocateInfo, 0, &memory);

    DeviceAllocation allocation;
    allocation.free = true;
    allocation.offset = 0;
    allocation.size = size;
    allocation.memory = memory;

    auto memoryPropertyFlag = device.memoryProperties.memoryTypes[memoryTypeIndex].propertyFlags;
    if (memoryPropertyFlag & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
    {
        vkMapMemory(device.handle, memory, 0, size, 0, &mapped_ptr);
        allocation.mapped_ptr = mapped_ptr;
    }
    allocations.emplace_back(allocation);
}

bool Acamarachi::Vulkan::DeviceMemoryChunk::alloc(Device &device, VkDeviceSize allocation_size, VkDeviceSize alignment, DeviceAllocation &allocation)
{
    if (allocation_size > size)
        return false;

    for (uint32_t i = 0; i < allocations.size(); i++)
    {
        auto current = allocations[i];
        if (current.free)
        {
            VkDeviceSize newSize = current.size;
            if (current.offset % alignment != 0)
            {
                newSize -= alignment - current.offset % alignment;
            }

            if (newSize >= allocation_size)
            {
                current.size = newSize;
                if (current.offset % alignment != 0)
                {
                    current.offset += alignment - current.offset % alignment;
                }

                if (mapped_ptr != nullptr)
                {
                    current.mapped_ptr = mapped_ptr + current.offset;
                }

                if (current.size == size) {
                    current.free = false;
                    allocation = current;
                    return true;
                }

                DeviceAllocation nextBlock;
                nextBlock.free = true;
                nextBlock.offset = current.offset + size;
                nextBlock.memory = memory;
                nextBlock.size = current.size - size;
                allocations.emplace_back(nextBlock);

                current.size = size;
                current.free = false;

                allocation = current;
                return true;
            }
        }
    }
    return false;
}

bool Acamarachi::Vulkan::DeviceMemoryChunk::ownsAllocation(DeviceAllocation &allocation)
{
    auto found = std::find(allocations.begin(), allocations.end(), allocation);
    return found == allocations.end();
}

void Acamarachi::Vulkan::DeviceMemoryChunk::dealloc(DeviceAllocation const &allocation)
{
    auto found = std::find(allocations.begin(), allocations.end(), allocation);
    if (found == allocations.end())
        return;

    found->free = true;
}
