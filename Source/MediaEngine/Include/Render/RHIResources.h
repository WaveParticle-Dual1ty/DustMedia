#pragma once
#include <string>
#include <vector>
#include "MediaEngine/Include/Core/Ptr.h"
#include "RHIPixelFormat.h"
#include "RHITexture.h"

namespace ME
{
struct RHICommandBuffer
{
    virtual ~RHICommandBuffer() = default;
};

struct RHIRenderPassCreateDesc
{
    ERHIPixelFormat PixelFormat = ERHIPixelFormat::PF_Unknown;
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

struct RHIShader
{
    virtual ~RHIShader() = default;

    ERHIShaderType Type = ERHIShaderType::Vertex;
    std::string EntryName;
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

struct RHISamplerCreateInfo
{
};

struct RHISampler
{
    virtual ~RHISampler() = default;
};

}  //namespace ME