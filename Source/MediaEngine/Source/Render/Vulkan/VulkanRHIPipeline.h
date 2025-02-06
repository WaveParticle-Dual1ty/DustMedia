#pragma once
#include "MediaEngine/Include/Render/RHIPipeline.h"
#include "vulkan/vulkan.h"

namespace ME
{
struct VulkanRHIGraphicPipeline : public RHIGraphicPipeline
{
    VkPipeline Pipeline = VK_NULL_HANDLE;
    VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
    std::vector<VkDescriptorSet> DescriptorSet;
};

}  //namespace ME