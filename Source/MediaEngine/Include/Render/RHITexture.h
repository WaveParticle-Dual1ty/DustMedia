#pragma once
#include <cstdint>
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
};

class RHITexture2D : public RHITexture
{
public:
    virtual ~RHITexture2D() = default;

public:
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
};

}  //namespace ME