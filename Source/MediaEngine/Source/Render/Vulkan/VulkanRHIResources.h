#pragma once
#include "MediaEngine/Include/Render/RHIResources.h"
#include "vulkan/vulkan.h"

namespace ME
{
struct VulkanRHICommandBuffer : RHICommandBuffer
{
    VkCommandBuffer CommandBuffer = VK_NULL_HANDLE;
};

struct VulkanRHIRenderPass : RHIRenderPass
{
    VkRenderPass RenderPass = VK_NULL_HANDLE;
};

struct VulkanRHIShader : RHIShader
{
    VkShaderModule ShaderModule = VK_NULL_HANDLE;
};

struct VulkanRHIGraphicPipeline : public RHIGraphicPipeline
{
    VkPipeline Pipeline = VK_NULL_HANDLE;
};

}  //namespace ME