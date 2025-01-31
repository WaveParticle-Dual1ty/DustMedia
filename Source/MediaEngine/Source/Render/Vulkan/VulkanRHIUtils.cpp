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

shaderc_shader_kind ConvertRHIShaderTypeToShaderKind(ERHIShaderType type)
{
    switch (type)
    {
        case ERHIShaderType::Vertex:
            return shaderc_vertex_shader;
        case ERHIShaderType::Pixel:
            return shaderc_fragment_shader;
        default:
            ME_ASSERT(false, "Not support ERHIShaderType now");
            return shaderc_vertex_shader;
    }
}

VkShaderStageFlagBits ConvertRHIShaderTypeToVkShaderStageFlagBits(ERHIShaderType type)
{
    switch (type)
    {
        case ERHIShaderType::Vertex:
            return VK_SHADER_STAGE_VERTEX_BIT;
        case ERHIShaderType::Pixel:
            return VK_SHADER_STAGE_FRAGMENT_BIT;
        default:
            ME_ASSERT(false, "Not support ERHIShaderType now");
            return VK_SHADER_STAGE_VERTEX_BIT;
    }
}

VkFormat ConvertERHIShaderDataTypeToVkFormat(ERHIShaderDataType type)
{
    switch (type)
    {
        case ERHIShaderDataType::None:
            ME_ASSERT(false, "ERHIShaderDataType is None");
            return VK_FORMAT_UNDEFINED;
        case ERHIShaderDataType::Float:
            return VK_FORMAT_R32_SFLOAT;
        case ERHIShaderDataType::Float2:
            return VK_FORMAT_R32G32_SFLOAT;
        case ERHIShaderDataType::Float3:
            return VK_FORMAT_R32G32B32_SFLOAT;
        case ERHIShaderDataType::Float4:
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        case ERHIShaderDataType::Mat3:
            ME_ASSERT(false, "Not supoort ERHIShaderDataType now");
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        case ERHIShaderDataType::Mat4:
            ME_ASSERT(false, "Not supoort ERHIShaderDataType now");
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        case ERHIShaderDataType::Int:
            ME_ASSERT(false, "Not supoort ERHIShaderDataType now");
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        case ERHIShaderDataType::Int2:
            ME_ASSERT(false, "Not supoort ERHIShaderDataType now");
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        case ERHIShaderDataType::Int3:
            ME_ASSERT(false, "Not supoort ERHIShaderDataType now");
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        case ERHIShaderDataType::Int4:
            ME_ASSERT(false, "Not supoort ERHIShaderDataType now");
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        case ERHIShaderDataType::Bool:
            ME_ASSERT(false, "Not supoort ERHIShaderDataType now");
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        default:
            ME_ASSERT(false, "Not supoort ERHIShaderDataType now");
            return VK_FORMAT_R32G32B32A32_SFLOAT;
    }
}

VkPrimitiveTopology ConvertRHIPrimitiveTopologyToVkPrimitiveTopology(RHIPrimitiveTopology type)
{
    switch (type)
    {
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_POINT_LIST:
            return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_LINE_LIST:
            return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_LINE_STRIP:
            return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST:
            return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP:
            return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN:
            return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY:
            return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY:
            return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY:
            return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY:
            return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_PATCH_LIST:
            return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
        case RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_MAX_ENUM:
            return VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
        default:
            ME_ASSERT(false, "Not supoort RHIPrimitiveTopology now");
            return VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
    }
}

VkBufferUsageFlagBits ConvertERHIBufferUsageToVkBufferUsageFlagBits(ERHIBufferUsage type)
{
    switch (type)
    {
        case ERHIBufferUsage::RHI_BUFFER_USAGE_TRANSFER_SRC_BIT:
            return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_TRANSFER_DST_BIT:
            return VK_BUFFER_USAGE_TRANSFER_DST_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT:
            return VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT:
            return VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_UNIFORM_BUFFER_BIT:
            return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_STORAGE_BUFFER_BIT:
            return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_INDEX_BUFFER_BIT:
            return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT:
            return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_INDIRECT_BUFFER_BIT:
            return VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT:
            return VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT:
            return VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT:
            return VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT:
            return VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR:
            return VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR:
            return VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR:
            return VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_RAY_TRACING_BIT_NV:
            return VK_BUFFER_USAGE_RAY_TRACING_BIT_NV;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_EXT:
            return VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_EXT;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_KHR:
            return VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT_KHR;
        case ERHIBufferUsage::RHI_BUFFER_USAGE_FLAG_BITS_MAX_ENUM:
            return VK_BUFFER_USAGE_FLAG_BITS_MAX_ENUM;
        default:
            ME_ASSERT(false, "Not supoort ERHIBufferUsage now");
            return VK_BUFFER_USAGE_FLAG_BITS_MAX_ENUM;
    }
}

VkShaderStageFlagBits ConvertERHIShaderStageToVkShaderStageFlagBits(ERHIShaderStage stage)
{
    switch (stage)
    {
        case ERHIShaderStage::RHI_SHADER_STAGE_VERTEX_BIT:
            return VK_SHADER_STAGE_VERTEX_BIT;
        case ERHIShaderStage::RHI_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
            return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        case ERHIShaderStage::RHI_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
            return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        case ERHIShaderStage::RHI_SHADER_STAGE_GEOMETRY_BIT:
            return VK_SHADER_STAGE_GEOMETRY_BIT;
        case ERHIShaderStage::RHI_SHADER_STAGE_FRAGMENT_BIT:
            return VK_SHADER_STAGE_FRAGMENT_BIT;
        case ERHIShaderStage::RHI_SHADER_STAGE_COMPUTE_BIT:
            return VK_SHADER_STAGE_COMPUTE_BIT;
        case ERHIShaderStage::RHI_SHADER_STAGE_ALL_GRAPHICS:
            return VK_SHADER_STAGE_ALL_GRAPHICS;
        default:
            ME_ASSERT(false, "Not supoort ERHIShaderStage type now");
            return VK_SHADER_STAGE_ALL_GRAPHICS;
    }
}

VkDescriptorType ConvertERHIDescriptorTypeToVkDescriptorType(ERHIDescriptorType type)
{
    switch (type)
    {
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_SAMPLER:
            return VK_DESCRIPTOR_TYPE_SAMPLER;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
            return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_SAMPLED_IMAGE:
            return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_STORAGE_IMAGE:
            return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER:
            return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER:
            return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
            return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER:
            return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC:
            return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC:
            return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_INPUT_ATTACHMENT:
            return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK:
            return VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR:
            return VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV:
            return VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_MUTABLE_VALVE:
            return VK_DESCRIPTOR_TYPE_MUTABLE_VALVE;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT:
            return VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT;
        case ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_MAX_ENUM:
            return VK_DESCRIPTOR_TYPE_MAX_ENUM;
        default:
            ME_ASSERT(false, "Not supoort ERHIDescriptorType type now");
            return VK_DESCRIPTOR_TYPE_MAX_ENUM;
    }
}

VkImageUsageFlags ConvertERHITextureUsageFlagsToVkImageUsageFlags(RHITextureUsageFlags flags)
{
    VkImageUsageFlags res = 0;

    if (flags & RHI_TEXTURE_USAGE_TRANSFER_SRC_BIT)
        res |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    if (flags & RHI_TEXTURE_USAGE_TRANSFER_DST_BIT)
        res |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
    if (flags & RHI_TEXTURE_USAGE_SAMPLED_BIT)
        res |= VK_IMAGE_USAGE_SAMPLED_BIT;
    if (flags & RHI_TEXTURE_USAGE_STORAGE_BIT)
        res |= VK_IMAGE_USAGE_STORAGE_BIT;
    if (flags & RHI_TEXTURE_USAGE_COLOR_ATTACHMENT_BIT)
        res |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    if (flags & RHI_TEXTURE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
        res |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    if (flags & RHI_TEXTURE_USAGE_TRANSIENT_ATTACHMENT_BIT)
        res |= VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT;
    if (flags & RHI_TEXTURE_USAGE_INPUT_ATTACHMENT_BIT)
        res |= VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT;
    if (flags & RHI_TEXTURE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT)
        res |= VK_IMAGE_USAGE_FRAGMENT_DENSITY_MAP_BIT_EXT;
    if (flags & RHI_TEXTURE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR)
        res |= VK_IMAGE_USAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR;
    if (flags & RHI_TEXTURE_USAGE_INVOCATION_MASK_BIT_HUAWEI)
        res |= VK_IMAGE_USAGE_INVOCATION_MASK_BIT_HUAWEI;
    if (flags & RHI_TEXTURE_USAGE_SHADING_RATE_IMAGE_BIT_NV)
        res |= VK_IMAGE_USAGE_SHADING_RATE_IMAGE_BIT_NV;

    return res;
}

VkMemoryPropertyFlags ConvertRHIMemoryPropertyFlagsToVkMemoryPropertyFlags(RHIMemoryPropertyFlags flags)
{
    VkMemoryPropertyFlags res = 0;

    if (flags & RHI_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
        res |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    if (flags & RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
        res |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
    if (flags & RHI_MEMORY_PROPERTY_HOST_COHERENT_BIT)
        res |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    if (flags & RHI_MEMORY_PROPERTY_HOST_CACHED_BIT)
        res |= VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
    if (flags & RHI_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
        res |= VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT;
    if (flags & RHI_MEMORY_PROPERTY_PROTECTED_BIT)
        res |= VK_MEMORY_PROPERTY_PROTECTED_BIT;
    if (flags & RHI_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD)
        res |= VK_MEMORY_PROPERTY_DEVICE_COHERENT_BIT_AMD;
    if (flags & RHI_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD)
        res |= VK_MEMORY_PROPERTY_DEVICE_UNCACHED_BIT_AMD;
    if (flags & RHI_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV)
        res |= VK_MEMORY_PROPERTY_RDMA_CAPABLE_BIT_NV;

    return res;
}

VkShaderStageFlags ConvertRHIShaderStageFlagsToVkShaderStageFlags(RHIShaderStageFlags flags)
{
    VkShaderStageFlags res = 0;

    if (flags & RHI_SHADER_STAGE_VERTEX_BIT)
        res |= VK_SHADER_STAGE_VERTEX_BIT;
    if (flags & RHI_SHADER_STAGE_TESSELLATION_CONTROL_BIT)
        res |= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
    if (flags & RHI_SHADER_STAGE_TESSELLATION_EVALUATION_BIT)
        res |= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
    if (flags & RHI_SHADER_STAGE_GEOMETRY_BIT)
        res |= VK_SHADER_STAGE_GEOMETRY_BIT;
    if (flags & RHI_SHADER_STAGE_FRAGMENT_BIT)
        res |= VK_SHADER_STAGE_FRAGMENT_BIT;
    if (flags & RHI_SHADER_STAGE_COMPUTE_BIT)
        res |= VK_SHADER_STAGE_COMPUTE_BIT;
    if (flags & RHI_SHADER_STAGE_ALL_GRAPHICS)
        res |= VK_SHADER_STAGE_ALL_GRAPHICS;
    if (flags & RHI_SHADER_STAGE_ALL)
        res |= VK_SHADER_STAGE_ALL;
    if (flags & RHI_SHADER_STAGE_RAYGEN_BIT_KHR)
        res |= VK_SHADER_STAGE_RAYGEN_BIT_KHR;
    if (flags & RHI_SHADER_STAGE_ANY_HIT_BIT_KHR)
        res |= VK_SHADER_STAGE_ANY_HIT_BIT_KHR;
    if (flags & RHI_SHADER_STAGE_CLOSEST_HIT_BIT_KHR)
        res |= VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR;
    if (flags & RHI_SHADER_STAGE_MISS_BIT_KHR)
        res |= VK_SHADER_STAGE_MISS_BIT_KHR;
    if (flags & RHI_SHADER_STAGE_INTERSECTION_BIT_KHR)
        res |= VK_SHADER_STAGE_INTERSECTION_BIT_KHR;
    if (flags & RHI_SHADER_STAGE_CALLABLE_BIT_KHR)
        res |= VK_SHADER_STAGE_CALLABLE_BIT_KHR;
    if (flags & RHI_SHADER_STAGE_TASK_BIT_NV)
        res |= VK_SHADER_STAGE_TASK_BIT_NV;
    if (flags & RHI_SHADER_STAGE_MESH_BIT_NV)
        res |= VK_SHADER_STAGE_MESH_BIT_NV;
    if (flags & RHI_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI)
        res |= VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI;
    if (flags & RHI_SHADER_STAGE_RAYGEN_BIT_NV)
        res |= VK_SHADER_STAGE_RAYGEN_BIT_NV;
    if (flags & RHI_SHADER_STAGE_ANY_HIT_BIT_NV)
        res |= VK_SHADER_STAGE_ANY_HIT_BIT_NV;
    if (flags & RHI_SHADER_STAGE_CLOSEST_HIT_BIT_NV)
        res |= VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV;
    if (flags & RHI_SHADER_STAGE_MISS_BIT_NV)
        res |= VK_SHADER_STAGE_MISS_BIT_NV;
    if (flags & RHI_SHADER_STAGE_INTERSECTION_BIT_NV)
        res |= VK_SHADER_STAGE_INTERSECTION_BIT_NV;
    if (flags & RHI_SHADER_STAGE_CALLABLE_BIT_NV)
        res |= VK_SHADER_STAGE_CALLABLE_BIT_NV;

    return res;
}

}  //namespace Util

}  //namespace ME