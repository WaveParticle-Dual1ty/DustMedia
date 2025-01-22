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
        case ERHIPixelFormat::PF_Unknown:
            res = VK_FORMAT_UNDEFINED;
            break;
        case ERHIPixelFormat::PF_R8_UNORM:
            res = VK_FORMAT_R8_UNORM;
            break;
        case ERHIPixelFormat::PF_R8G8_UNORM:
            res = VK_FORMAT_R8G8_UNORM;
            break;
        case ERHIPixelFormat::PF_R8G8B8_UNORM:
            res = VK_FORMAT_R8G8B8_UNORM;
            break;
        case ERHIPixelFormat::PF_R8G8B8A8_UNORM:
            res = VK_FORMAT_R8G8B8A8_UNORM;
            break;
        default:
            res = VK_FORMAT_UNDEFINED;
            ME_ASSERT(false, "Not support now");
            break;
    }

    return res;
}

VkPipelineStageFlags ConvertERHIPipelineStageFlagToVkPipelineStageFlags(ERHIPipelineStageFlag flag)
{
    VkPipelineStageFlags res;

    switch (flag)
    {
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_TOP_OF_PIPE_BIT:
            res = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_DRAW_INDIRECT_BIT:
            res = VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_VERTEX_INPUT_BIT:
            res = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_VERTEX_SHADER_BIT:
            res = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT:
            res = VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT:
            res = VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_GEOMETRY_SHADER_BIT:
            res = VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT:
            res = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT:
            res = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT:
            res = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT:
            res = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COMPUTE_SHADER_BIT:
            res = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_TRANSFER_BIT:
            res = VK_PIPELINE_STAGE_TRANSFER_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT:
            res = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_HOST_BIT:
            res = VK_PIPELINE_STAGE_HOST_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_ALL_GRAPHICS_BIT:
            res = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_ALL_COMMANDS_BIT:
            res = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_NONE:
            res = VK_PIPELINE_STAGE_NONE;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT:
            res = VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT:
            res = VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR:
            res = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR:
            res = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_TASK_SHADER_BIT_NV:
            res = VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_MESH_SHADER_BIT_NV:
            res = VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT:
            res = VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR:
            res = VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV:
            res = VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV:
            res = VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV:
            res = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV:
            res = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_NONE_KHR:
            res = VK_PIPELINE_STAGE_NONE_KHR;
            break;
        case ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_FLAG_BITS_MAX_ENUM:
            res = VK_PIPELINE_STAGE_FLAG_BITS_MAX_ENUM;
            break;
        default:
            ME_ASSERT(false, "Not support ERHIPipelineStageFlag convert")
            res = VK_PIPELINE_STAGE_FLAG_BITS_MAX_ENUM;
            break;
    }

    return res;
}

VkAccessFlags ConvertERHIAccessFlagToVkAccessFlags(ERHIAccessFlag flag)
{
    VkAccessFlags res;

    switch (flag)
    {
        case ERHIAccessFlag::RHI_ACCESS_INDIRECT_COMMAND_READ_BIT:
            res = VK_ACCESS_INDIRECT_COMMAND_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_INDEX_READ_BIT:
            res = VK_ACCESS_INDEX_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_VERTEX_ATTRIBUTE_READ_BIT:
            res = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_UNIFORM_READ_BIT:
            res = VK_ACCESS_UNIFORM_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_INPUT_ATTACHMENT_READ_BIT:
            res = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_SHADER_READ_BIT:
            res = VK_ACCESS_SHADER_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_SHADER_WRITE_BIT:
            res = VK_ACCESS_SHADER_WRITE_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT:
            res = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT:
            res = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT:
            res = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT:
            res = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_TRANSFER_READ_BIT:
            res = VK_ACCESS_TRANSFER_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_TRANSFER_WRITE_BIT:
            res = VK_ACCESS_TRANSFER_WRITE_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_HOST_READ_BIT:
            res = VK_ACCESS_HOST_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_HOST_WRITE_BIT:
            res = VK_ACCESS_HOST_WRITE_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_MEMORY_READ_BIT:
            res = VK_ACCESS_MEMORY_READ_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_MEMORY_WRITE_BIT:
            res = VK_ACCESS_MEMORY_WRITE_BIT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_NONE:
            res = VK_ACCESS_NONE;
            break;
        case ERHIAccessFlag::RHI_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT:
            res = VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT:
            res = VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT:
            res = VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT:
            res = VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT:
            res = VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR:
            res = VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR;
            break;
        case ERHIAccessFlag::RHI_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR:
            res = VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR;
            break;
        case ERHIAccessFlag::RHI_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT:
            res = VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT;
            break;
        case ERHIAccessFlag::RHI_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR:
            res = VK_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR;
            break;
        case ERHIAccessFlag::RHI_ACCESS_COMMAND_PREPROCESS_READ_BIT_NV:
            res = VK_ACCESS_COMMAND_PREPROCESS_READ_BIT_NV;
            break;
        case ERHIAccessFlag::RHI_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV:
            res = VK_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV;
            break;
        case ERHIAccessFlag::RHI_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV:
            res = VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV;
            break;
        case ERHIAccessFlag::RHI_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV:
            res = VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_NV;
            break;
        case ERHIAccessFlag::RHI_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV:
            res = VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_NV;
            break;
        case ERHIAccessFlag::RHI_ACCESS_NONE_KHR:
            res = VK_ACCESS_NONE_KHR;
            break;
        case ERHIAccessFlag::RHI_ACCESS_FLAG_BITS_MAX_ENUM:
            res = VK_ACCESS_FLAG_BITS_MAX_ENUM;
            break;
        default:
            ME_ASSERT(false, "Not support ERHIAccessFlag convert")
            res = VK_ACCESS_FLAG_BITS_MAX_ENUM;
            break;
    }

    return VkAccessFlags();
}

VkImageAspectFlags ConvertERHIImageAspectFlagToVkImageAspectFlags(ERHIImageAspectFlag flag)
{
    VkImageAspectFlags res;

    switch (flag)
    {
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_COLOR_BIT:
            res = VK_IMAGE_ASPECT_COLOR_BIT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_DEPTH_BIT:
            res = VK_IMAGE_ASPECT_DEPTH_BIT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_STENCIL_BIT:
            res = VK_IMAGE_ASPECT_STENCIL_BIT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_METADATA_BIT:
            res = VK_IMAGE_ASPECT_METADATA_BIT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_PLANE_0_BIT:
            res = VK_IMAGE_ASPECT_PLANE_0_BIT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_PLANE_1_BIT:
            res = VK_IMAGE_ASPECT_PLANE_1_BIT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_PLANE_2_BIT:
            res = VK_IMAGE_ASPECT_PLANE_2_BIT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_NONE:
            res = VK_IMAGE_ASPECT_NONE;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT:
            res = VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT:
            res = VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT:
            res = VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT:
            res = VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_PLANE_0_BIT_KHR:
            res = VK_IMAGE_ASPECT_PLANE_0_BIT_KHR;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_PLANE_1_BIT_KHR:
            res = VK_IMAGE_ASPECT_PLANE_1_BIT_KHR;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_PLANE_2_BIT_KHR:
            res = VK_IMAGE_ASPECT_PLANE_2_BIT_KHR;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_NONE_KHR:
            res = VK_IMAGE_ASPECT_NONE_KHR;
            break;
        case ERHIImageAspectFlag::RHI_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM:
            res = VK_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM;
            break;
        default:
            ME_ASSERT(false, "Not support ERHIImageAspectFlag convert")
            res = VK_IMAGE_ASPECT_FLAG_BITS_MAX_ENUM;
            break;
    }

    return res;
}

VkImageLayout ConvertERHIImageLayoutToVkImageLayout(ERHIImageLayout flag)
{
    VkImageLayout res;

    switch (flag)
    {
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED:
            res = VK_IMAGE_LAYOUT_UNDEFINED;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_GENERAL:
            res = VK_IMAGE_LAYOUT_GENERAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
            res = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
            res = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL:
            res = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
            res = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
            res = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
            res = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_PREINITIALIZED:
            res = VK_IMAGE_LAYOUT_PREINITIALIZED;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL:
            res = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL:
            res = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL:
            res = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL:
            res = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL:
            res = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL:
            res = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_READ_ONLY_OPTIMAL:
            res = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL:
            res = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_PRESENT_SRC_KHR:
            res = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_SHARED_PRESENT_KHR:
            res = VK_IMAGE_LAYOUT_SHARED_PRESENT_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT:
            res = VK_IMAGE_LAYOUT_FRAGMENT_DENSITY_MAP_OPTIMAL_EXT;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR:
            res = VK_IMAGE_LAYOUT_FRAGMENT_SHADING_RATE_ATTACHMENT_OPTIMAL_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR:
            res = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR:
            res = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV:
            res = VK_IMAGE_LAYOUT_SHADING_RATE_OPTIMAL_NV;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL_KHR:
            res = VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL_KHR:
            res = VK_IMAGE_LAYOUT_DEPTH_READ_ONLY_OPTIMAL_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL_KHR:
            res = VK_IMAGE_LAYOUT_STENCIL_ATTACHMENT_OPTIMAL_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL_KHR:
            res = VK_IMAGE_LAYOUT_STENCIL_READ_ONLY_OPTIMAL_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR:
            res = VK_IMAGE_LAYOUT_READ_ONLY_OPTIMAL_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR:
            res = VK_IMAGE_LAYOUT_ATTACHMENT_OPTIMAL_KHR;
            break;
        case ERHIImageLayout::RHI_IMAGE_LAYOUT_MAX_ENUM:
            res = VK_IMAGE_LAYOUT_MAX_ENUM;
            break;
        default:
            ME_ASSERT(false, "Not support ERHIImageLayout convert")
            res = VK_IMAGE_LAYOUT_MAX_ENUM;
            break;
    }

    return res;
}
}  //namespace Util

}  //namespace ME