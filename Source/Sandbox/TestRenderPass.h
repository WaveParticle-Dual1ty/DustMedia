#pragma once
#include "MediaEngine/Include/Render/RenderPass.h"
using namespace ME;

class TestRenderPass : public ME::FRenderPass
{
public:
    TestRenderPass(Ref<RHI> rhi);

public:
    virtual bool Initialize(uint32_t w, uint32_t h) override;
    virtual bool Resize(uint32_t w, uint32_t h) override;
    virtual bool Draw(Ref<RHICommandBuffer> cmdBuffer) override;

    Ref<RHITexture2D> GetTargetTexture();

private:
    std::vector<Ref<RHITexture2D>> m_TargetTextures;
};
