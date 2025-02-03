#pragma once
#include "MediaEngine/Include/Render/RenderPass.h"
#include "MediaEngine/Include/Render/RHIPixelFormat.h"

namespace ME
{
class ImGuiRenderPass : public FRenderPass
{
public:
    ImGuiRenderPass(Ref<RHI> rhi);

public:
    virtual bool Initialize(uint32_t w, uint32_t h) override;
    virtual bool Resize(uint32_t w, uint32_t h) override;
    virtual bool Draw(Ref<RHICommandBuffer> cmdBuffer) override;

public:
    void SetSwapchainFormat(ERHIPixelFormat format);

private:
    std::vector<Ref<RHITexture2D>> m_TargetTextures;
    ERHIPixelFormat m_SwapchainFormat = ERHIPixelFormat::PF_Unknown;
};

}  //namespace ME
