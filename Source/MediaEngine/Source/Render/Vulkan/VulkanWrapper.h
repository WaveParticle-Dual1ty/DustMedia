#pragma once
#include "MediaEngine/Include/Core/PlatformDetection.h"

#ifdef ME_PLATFORM_WINDOWS
#define VK_USE_PLATFORM_WIN32_KHR
#elif defined(ME_PLATFORM_MACOS)
// todo
#else
#error "Unsupport Plarform"
#endif  // PLATFORM_WINDOWS
#include "vulkan/vulkan.h"

namespace ME
{
class VulkanWrapper
{
public:
    static VkBool32 vkGetPhysicalDevicePresentationSupport(
        VkInstance instance,
        VkPhysicalDevice physicalDevice,
        uint32_t queueFamilyIndex);

private:
};

}  //namespace ME
