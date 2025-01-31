#pragma once
#include <array>
#include "ThirdParty/stb/stb_image.h"
#include "MediaEngine/Include/Render/RHIBuffer.h"
#include "MediaEngine/Include/Render/RHIDescriptorSet.h"
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
    struct Vertex
    {
        std::array<float, 4> Position = {0, 0, 0, 0};
        std::array<float, 4> Color = {0, 0, 0, 0};
        std::array<float, 2> Texcoord = {0, 0};
    };

    struct Index
    {
        uint32_t Index1 = 0;
        uint32_t Index2 = 0;
        uint32_t Index3 = 0;
    };

    struct ConstantData
    {
        RHIColor Color;
    };

    std::vector<Ref<RHITexture2D>> m_TargetTextures;
    void* m_TargetImTextureID = nullptr;
    std::array<float, 4> m_ClearColor = {0, 0, 0, 1};

    Ref<RHIShader> m_VertexShader;
    Ref<RHIShader> m_PixelShader;
    Ref<RHIDescriptorSet> m_DescriptorSet;
    std::vector<Ref<RHIDescriptorSet>> m_DescriptorSets;

    Ref<RHIGraphicPipeline> m_Pipeline;

    Ref<RHIBuffer> m_VertexBuffer;
    Ref<RHIBuffer> m_IndexBuffer;
    Ref<RHITexture2D> m_Texture;
    Ref<RHIBuffer> m_ImageBuffer;

    bool m_UploadTexture = false;
};
