#include "MediaEngine/Include/Render/RenderPass.h"

namespace ME
{
FRenderPass::FRenderPass(Ref<RHI> rhi)
    : m_RHI(rhi)
{
}

bool FRenderPass::Initialize(uint32_t w, uint32_t h)
{
    m_Width = w;
    m_Height = h;
    return true;
}

bool FRenderPass::Resize(uint32_t w, uint32_t h)
{
    return true;
}

bool FRenderPass::Draw(Ref<RHICommandBuffer> cmdBuffer)
{
    return true;
}

void FRenderPass::Destroy()
{
}

Ref<RHIRenderPass> FRenderPass::GetRHIRenderPass()
{
    return m_RHIRenderPass;
}

Ref<RHIFramebuffer> FRenderPass::GetFramebuffer()
{
    return m_RHIFrameBuffer;
}

}  //namespace ME