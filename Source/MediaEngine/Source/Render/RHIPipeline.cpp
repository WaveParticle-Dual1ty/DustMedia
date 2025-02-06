#include "MediaEngine/Include/Render/RHIPipeline.h"
#include "MediaEngine/Include/Core/Assert.h"

namespace ME
{
uint32_t GetRHIShaderDataTypeSize(ERHIShaderDataType type)
{
    switch (type)
    {
        case ERHIShaderDataType::None:
            ME_ASSERT(false, "ERHIShaderDataType is None");
            return 0;
        case ERHIShaderDataType::Float:
            return 4;
        case ERHIShaderDataType::Float2:
            return 4 * 2;
        case ERHIShaderDataType::Float3:
            return 4 * 3;
        case ERHIShaderDataType::Float4:
            return 4 * 4;
        case ERHIShaderDataType::Mat3:
            return 4 * 3 * 3;
        case ERHIShaderDataType::Mat4:
            return 4 * 4 * 4;
        case ERHIShaderDataType::Int:
            return 4;
        case ERHIShaderDataType::Int2:
            return 4 * 2;
        case ERHIShaderDataType::Int3:
            return 4 * 3;
        case ERHIShaderDataType::Int4:
            return 4 * 4;
        case ERHIShaderDataType::Bool:
            return 1;
        default:
            ME_ASSERT(false, "Not support ERHIShaderDataType now");
            return 0;
    }
}

const std::vector<RHIVertexElement>& RHIVertexInputLayout::GetElements()
{
    return m_Elements;
}

uint32_t RHIVertexInputLayout::GetStride() const
{
    return m_Stride;
}

void RHIVertexInputLayout::CalculateOffsetAndStride()
{
    uint32_t offset = 0;
    for (auto& element : m_Elements)
    {
        element.Offset = offset;
        offset += element.Size;
        m_Stride += element.Size;
    }
}

}  //namespace ME