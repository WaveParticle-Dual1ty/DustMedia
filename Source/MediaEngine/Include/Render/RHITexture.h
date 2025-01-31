#pragma once
#include <cstdint>
#include "RHIEnums.h"
#include "RHIPixelFormat.h"

namespace ME
{
class RHITexture
{
public:
    virtual ~RHITexture() = default;
};

struct RHITexture2DCreateDesc
{
    ERHIPixelFormat PixelFormat = ERHIPixelFormat::PF_Unknown;
    uint32_t Width = 0;
    uint32_t Height = 0;
    uint32_t NumMips = 0;
    uint32_t NumSamples = 0;
    RHITextureUsageFlags Usage = 0;
    RHIMemoryPropertyFlags MemoryProperty = 0;
};

class RHITexture2D : public RHITexture
{
public:
    virtual ~RHITexture2D() = default;

public:
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;

protected:
    ERHIPixelFormat m_PixelFormat = ERHIPixelFormat::PF_Unknown;
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
};

}  //namespace ME