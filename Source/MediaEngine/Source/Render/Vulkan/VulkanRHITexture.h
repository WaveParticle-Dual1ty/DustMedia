#pragma once
#include "vulkan/vulkan.h"
#include "MediaEngine/Include/Render/RHITexture.h"

namespace ME
{
class VulkanRHITexture2D : public RHITexture2D
{
public:
private:
    VkFormat m_VKFormat = VK_FORMAT_UNDEFINED;
    VkImage m_Image = VK_NULL_HANDLE;
    VkDeviceMemory m_DeviceMem = VK_NULL_HANDLE;
    VkImageView m_ImageView = VK_NULL_HANDLE;

private:
    friend class VulkanRHI;
};

}  //namespace ME