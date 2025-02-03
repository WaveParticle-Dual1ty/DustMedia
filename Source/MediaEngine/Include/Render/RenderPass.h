#pragma once
#include <cstdint>
#include "RHI.h"
#include "RHIResources.h"
#include "RHIFramebuffer.h"

namespace ME
{
class FRenderPass
{
public:
    FRenderPass(Ref<RHI> rhi);
    virtual ~FRenderPass() = default;

public:
    virtual bool Initialize(uint32_t w, uint32_t h);
    virtual bool Resize(uint32_t w, uint32_t h);
    virtual bool Draw(Ref<RHICommandBuffer> cmdBuffer);
    virtual void Destroy();

public:
    Ref<RHIRenderPass> GetRHIRenderPass();
    Ref<RHIFramebuffer> GetFramebuffer();

protected:
    uint32_t m_Width = 0;
    uint32_t m_Height = 0;
    Ref<RHI> m_RHI;
    Ref<RHIRenderPass> m_RHIRenderPass;
    Ref<RHIFramebuffer> m_RHIFrameBuffer;
};

}  //namespace ME
