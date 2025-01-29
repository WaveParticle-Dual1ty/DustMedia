#pragma once
#include <string>
#include <vector>
#include "MediaEngine/Include/Core/Ptr.h"

namespace ME
{
struct RHICommandBuffer
{
    virtual ~RHICommandBuffer() = default;
};

struct RHIRenderPassCreateDesc
{
};

struct RHIRenderPass
{
    virtual ~RHIRenderPass() = default;
};

enum class ERHIShaderType
{
    Vertex,
    Pixel,
};

struct RHIShaderCreateInfo
{
    ERHIShaderType Type = ERHIShaderType::Vertex;
    std::string ShaderFile;
    std::string EntryName;
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

struct RHIShader
{
    virtual ~RHIShader() = default;

    ERHIShaderType Type = ERHIShaderType::Vertex;
    std::string EntryName;
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

struct RHIGraphicPipelineCreateInfo
{
    std::vector<Ref<RHIShader>> Shaders;
    RHIVertexInputLayout VertexInputLayout;
    RHIInputAssemblyInfo InputAssemblyInfo;
    Ref<RHIRenderPass> RenderPass;
};

struct RHIGraphicPipeline
{
    virtual ~RHIGraphicPipeline() = default;
};

struct RHIViewport
{
    float X = 0;
    float Y = 0;
    float Width = 0;
    float Height = 0;
    float MinDepth = 0;
    float MaxDepth = 1;

    RHIViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        : X(static_cast<float>(x))
        , Y(static_cast<float>(y))
        , Width(static_cast<float>(width))
        , Height(static_cast<float>(height))
    {
    }

    RHIViewport(float x, float y, float width, float height)
        : X(x)
        , Y(y)
        , Width(width)
        , Height(height)
    {
    }

    RHIViewport(float x, float y, float width, float height, float minDepth, float maxDepth)
        : X(x)
        , Y(y)
        , Width(width)
        , Height(height)
        , MinDepth(minDepth)
        , MaxDepth(maxDepth)
    {
    }
};

struct RHIScissor
{
    int32_t OffsetX;
    int32_t OffsetY;
    uint32_t Width = 0;
    uint32_t Height = 0;
};

}  //namespace ME