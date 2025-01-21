#include "VulkanRHIUtils.h"
#include "MediaEngine/Include/Core/Assert.h"

namespace ME
{
namespace Util
{
VkFormat ConvertERHIPixelFormatToVkFormat(ERHIPixelFormat format)
{
    VkFormat res = VK_FORMAT_UNDEFINED;

    switch (format)
    {
        case ME::ERHIPixelFormat::PF_Unknown:
            res = VK_FORMAT_UNDEFINED;
            break;
        case ME::ERHIPixelFormat::PF_R8_UNORM:
            res = VK_FORMAT_R8_UNORM;
            break;
        case ME::ERHIPixelFormat::PF_R8G8_UNORM:
            res = VK_FORMAT_R8G8_UNORM;
            break;
        case ME::ERHIPixelFormat::PF_R8G8B8_UNORM:
            res = VK_FORMAT_R8G8B8_UNORM;
            break;
        case ME::ERHIPixelFormat::PF_R8G8B8A8_UNORM:
            res = VK_FORMAT_R8G8B8A8_UNORM;
            break;
        default:
            res = VK_FORMAT_UNDEFINED;
            ME_ASSERT(false, "Not support now");
            break;
    }

    return res;
}
}  //namespace Util

}  //namespace ME