#pragma once
#include <array>
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
    void UpdateImageBuffer(uint32_t w, uint32_t h, ME::Ref<ME::RHIBuffer> buffer);

public:
    void* GetTargetImTextureID();
    bool CreateGraphicPipelineAndResources();

private:
    struct Vertex
    {
        std::array<float, 2> Position = {0, 0};
        std::array<float, 2> Texcoord = {0, 0};
    };

    struct Index
    {
        uint32_t Index1 = 0;
        uint32_t Index2 = 0;
        uint32_t Index3 = 0;
    };

    std::vector<ME::Ref<ME::RHITexture2D>> m_TargetTextures;
    void* m_TargetImTextureID = nullptr;

    ME::Ref<ME::RHIDescriptorSet> m_DescriptorSet;
    std::vector<ME::Ref<ME::RHIDescriptorSet>> m_DescriptorSets;
    ME::Ref<ME::RHISampler> m_Sampler;
    ME::Ref<ME::RHIShader> m_VertexShader;
    ME::Ref<ME::RHIShader> m_PixelShader;
    ME::Ref<ME::RHIGraphicPipeline> m_Pipeline;

    ME::Ref<ME::RHIBuffer> m_VertexBuffer;
    ME::Ref<ME::RHIBuffer> m_IndexBuffer;

    ME::Ref<ME::RHIBuffer> m_TextureBuffer;
    ME::Ref<ME::RHITexture2D> m_Texture;
    bool m_UploadTexture = false;
};
