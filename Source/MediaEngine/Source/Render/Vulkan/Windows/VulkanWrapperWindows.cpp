#include "../VulkanWrapper.h"
#include "MediaEngine/Include/Core/PlatformDetection.h"

#ifdef ME_PLATFORM_WINDOWS

namespace ME
{
VkBool32 VulkanWrapper::vkGetPhysicalDevicePresentationSupport(
    VkInstance instance,
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndex)
{
    static_cast<void>(instance);
    return vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, queueFamilyIndex);
}

}  //namespace ME

#endif  // ME_PLATFORM_MACOS
