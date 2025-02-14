﻿#pragma once
#include "vulkan/vulkan.h"
#include "shaderc/shaderc.hpp"
#include "MediaEngine/Include/Render/RHIEnums.h"
#include "MediaEngine/Include/Render/RHIPixelFormat.h"
#include "MediaEngine/Include/Render/RHIStruct.h"
#include "MediaEngine/Include/Render/RHIResources.h"
#include "MediaEngine/Include/Render/RHIBuffer.h"
#include "MediaEngine/Include/Render/RHITexture.h"
#include "MediaEngine/Include/Render/RHIPipeline.h"

namespace ME
{
namespace Util
{
VkFormat ConvertERHIPixelFormatToVkFormat(ERHIPixelFormat format);
ERHIPixelFormat ConvertVkFormatToERHIPixelFormat(VkFormat format);

VkPipelineStageFlags ConvertERHIPipelineStageFlagToVkPipelineStageFlags(ERHIPipelineStageFlag flag);
VkAccessFlags ConvertERHIAccessFlagToVkAccessFlags(ERHIAccessFlag flag);
VkImageAspectFlags ConvertERHIImageAspectFlagToVkImageAspectFlags(ERHIImageAspectFlag flag);
VkImageLayout ConvertERHIImageLayoutToVkImageLayout(ERHIImageLayout flag);
shaderc_shader_kind ConvertRHIShaderTypeToShaderKind(ERHIShaderType type);
VkShaderStageFlagBits ConvertRHIShaderTypeToVkShaderStageFlagBits(ERHIShaderType type);
VkFormat ConvertERHIShaderDataTypeToVkFormat(ERHIShaderDataType type);
VkPrimitiveTopology ConvertRHIPrimitiveTopologyToVkPrimitiveTopology(RHIPrimitiveTopology type);
VkShaderStageFlagBits ConvertERHIShaderStageToVkShaderStageFlagBits(ERHIShaderStage stage);
VkDescriptorType ConvertERHIDescriptorTypeToVkDescriptorType(ERHIDescriptorType type);
VkImageUsageFlags ConvertERHITextureUsageFlagsToVkImageUsageFlags(RHITextureUsageFlags flags);
VkMemoryPropertyFlags ConvertRHIMemoryPropertyFlagsToVkMemoryPropertyFlags(RHIMemoryPropertyFlags flags);
VkShaderStageFlags ConvertRHIShaderStageFlagsToVkShaderStageFlags(RHIShaderStageFlags flags);
VkBufferUsageFlags ConvertRHIBufferUsageFlagsToVkBufferUsageFlags(RHIBufferUsageFlags flags);

}  //namespace Util

}  //namespace ME
