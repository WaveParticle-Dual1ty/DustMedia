#pragma once
#include "vulkan/vulkan.h"
#include "MediaEngine/Include/Render/RHIFramebuffer.h"

namespace ME
{
class VulkanRHIFrameBuffer : public RHIFramebuffer
{
public:
private:
    VkFramebuffer m_Framebuffer = VK_NULL_HANDLE;

private:
    friend class VulkanRHI;
};

}  //namespace ME