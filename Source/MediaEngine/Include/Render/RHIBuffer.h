#pragma once
#include <cstdint>
#include "RHIEnums.h"

namespace ME
{
struct RHIBufferCreateDesc
{
    RHIBufferUsageFlags Usage = 0;
    RHIMemoryPropertyFlags MemoryProperty = 0;
    uint64_t BufferSize = 0;
    void* Data = nullptr;
};

struct RHIBuffer
{
    virtual ~RHIBuffer() = default;
};

}  //namespace ME