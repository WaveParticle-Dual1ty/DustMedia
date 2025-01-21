#pragma once

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

}  //namespace ME