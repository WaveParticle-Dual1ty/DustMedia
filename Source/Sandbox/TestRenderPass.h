#pragma once
#include <array>
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

public:
    void* GetTargetImTextureID();
    void SetColor(std::array<float, 4> color);

private:
    std::vector<Ref<RHITexture2D>> m_TargetTextures;
    void* m_TargetImTextureID = nullptr;
    std::array<float, 4> m_ClearColor = {0, 0, 0, 1};
};
