#pragma once
#include "MediaEngine/Include/Render/RenderPass.h"

class ImageRenderPass : ME::FRenderPass
{
public:
    ImageRenderPass(ME::Ref<ME::RHI> rhi);

public:
    virtual bool Initialize(uint32_t w, uint32_t h) override;
    virtual bool Resize(uint32_t w, uint32_t h) override;
    virtual bool Draw(ME::Ref<ME::RHICommandBuffer> cmdBuffer) override;

public:
    void* GetTargetImTextureID();

private:
    std::vector<ME::Ref<ME::RHITexture2D>> m_TargetTextures;
    void* m_TargetImTextureID = nullptr;
};
