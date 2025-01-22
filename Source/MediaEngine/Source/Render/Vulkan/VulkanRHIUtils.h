#pragma once
#include "vulkan/vulkan.h"
#include "MediaEngine/Include/Render/RHIPixelFormat.h"
#include "MediaEngine/Include/Render/RHIStruct.h"

namespace ME
{
namespace Util
{
VkFormat ConvertERHIPixelFormatToVkFormat(ERHIPixelFormat format);
VkPipelineStageFlags ConvertERHIPipelineStageFlagToVkPipelineStageFlags(ERHIPipelineStageFlag flag);
VkAccessFlags ConvertERHIAccessFlagToVkAccessFlags(ERHIAccessFlag flag);
VkImageAspectFlags ConvertERHIImageAspectFlagToVkImageAspectFlags(ERHIImageAspectFlag flag);
VkImageLayout ConvertERHIImageLayoutToVkImageLayout(ERHIImageLayout flag);

}  //namespace Util

}  //namespace ME