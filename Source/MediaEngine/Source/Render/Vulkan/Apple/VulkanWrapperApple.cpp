#include "../VulkanWrapper.h"
#include "MediaEngine/Include/Core/PlatformDetection.h"

#ifdef ME_PLATFORM_MACOS

namespace ME
{
VkBool32 VulkanWrapper::vkGetPhysicalDevicePresentationSupport(
    VkInstance instance,
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex)
{
    static_cast<void>(instance);
    static_cast<void>(physicalDevice);
    static_cast<void>(queueFamilyIndex);
    return VK_TRUE;
}

}  //namespace ME
#endif  // ME_PLATFORM_MACOS
