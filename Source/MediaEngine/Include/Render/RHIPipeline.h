#pragma once
#include <vector>
#include "RHIResources.h"
#include "RHIDescriptorSet.h"

namespace ME
{
struct RHIPipeline
{
};

enum class ERHIShaderDataType
{
    None,
    Float,
    Float2,
    Float3,
    Float4,
    Mat3,
    Mat4,
    Int,
    Int2,
    Int3,
    Int4,
    Bool
};

uint32_t GetRHIShaderDataTypeSize(ERHIShaderDataType type);

struct RHIVertexElement
{
    std::string Name;
    ERHIShaderDataType Type;
    uint32_t Location = 0;

    uint32_t Size = 0;
    uint32_t Offset = 0;

    RHIVertexElement(const std::string& name, ERHIShaderDataType type, uint32_t location)
        : Name(name)
        , Type(type)
        , Location(location)
        , Size(GetRHIShaderDataTypeSize(type))
    {
    }
};

class RHIVertexInputLayout
{
public:
    RHIVertexInputLayout() = default;

    RHIVertexInputLayout(const std::initializer_list<RHIVertexElement>& elements)
        : m_Elements(elements)
    {
        CalculateOffsetAndStride();
    }

public:
    const std::vector<RHIVertexElement>& GetElements();
    uint32_t GetStride() const;

private:
    void CalculateOffsetAndStride();

private:
    std::vector<RHIVertexElement> m_Elements;
    uint32_t m_Stride = 0;
};

enum class RHIPrimitiveTopology
{
    RHI_PRIMITIVE_TOPOLOGY_POINT_LIST,
    RHI_PRIMITIVE_TOPOLOGY_LINE_LIST,
    RHI_PRIMITIVE_TOPOLOGY_LINE_STRIP,
    RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
    RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP,
    RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
    RHI_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY,
    RHI_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY,
    RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY,
    RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY,
    RHI_PRIMITIVE_TOPOLOGY_PATCH_LIST,
    RHI_PRIMITIVE_TOPOLOGY_MAX_ENUM
};

struct RHIInputAssemblyInfo
{
    RHIPrimitiveTopology PrimitiveTopology;
};

enum class ERHIShaderStage : uint32_t
{
    RHI_SHADER_STAGE_VERTEX_BIT,
    RHI_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
    RHI_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
    RHI_SHADER_STAGE_GEOMETRY_BIT,
    RHI_SHADER_STAGE_FRAGMENT_BIT,
    RHI_SHADER_STAGE_COMPUTE_BIT,
    RHI_SHADER_STAGE_ALL_GRAPHICS,
};

struct RHIConstantRange
{
    ERHIShaderStage ShaderStage = ERHIShaderStage::RHI_SHADER_STAGE_VERTEX_BIT;
    uint32_t Size = 0;
};

struct RHISetLayoutBinding
{
    uint32_t Binding = 0;
    ERHIDescriptorType DescriptorType = ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_MAX_ENUM;
    ERHIShaderStage ShaderStage = ERHIShaderStage::RHI_SHADER_STAGE_VERTEX_BIT;
};

struct RHISetLayoutDesc
{
    std::vector<RHISetLayoutBinding> SetLayoutBindings;
};

struct RHIGraphicPipelineCreateInfo
{
    std::vector<Ref<RHIShader>> Shaders;
    RHIVertexInputLayout VertexInputLayout;
    RHIInputAssemblyInfo InputAssemblyInfo;
    Ref<RHIRenderPass> RenderPass;
    std::vector<RHIConstantRange> ConstantRanges;
    std::vector<RHISetLayoutDesc> SetLayoutDescs;
    std::vector<Ref<RHIDescriptorSet>> DescriptorSet;
};

struct RHIGraphicPipeline
{
    virtual ~RHIGraphicPipeline() = default;
};

}  //namespace ME
