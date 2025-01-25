#include "TestRenderPass.h"
#include "SandboxLog.h"

TestRenderPass::TestRenderPass(Ref<RHI> rhi)
    : FRenderPass(rhi)
{
}

bool TestRenderPass::Initialize(uint32_t w, uint32_t h)
{
    RHIRenderPassCreateDesc desc;
    m_RHIRenderPass = m_RHI->CreateRHIRenderPass(desc);
    if (!m_RHIRenderPass)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHIRenderPass fail");
        return false;
    }

    RHITexture2DCreateDesc texCreateDesc;
    texCreateDesc.PixelFormat = ERHIPixelFormat::PF_R8G8B8A8_UNORM;
    texCreateDesc.Width = w;
    texCreateDesc.Height = h;
    texCreateDesc.NumMips = 1;
    texCreateDesc.NumSamples = 1;

    Ref<RHITexture2D> targetTex = m_RHI->CreateRHITexture2D(texCreateDesc);
    if (!targetTex)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHITexture2D fail");
        return false;
    }

    m_TargetTextures.push_back(targetTex);
    m_RHIFrameBuffer = m_RHI->CreateRHIFramebuffer(w, h, m_RHIRenderPass, m_TargetTextures);
    if (!m_RHIFrameBuffer)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHIFramebuffer fail");
        return false;
    }

    m_TargetImTextureID = m_RHI->CreateImTextureID(targetTex);

    return true;
}

bool TestRenderPass::Resize(uint32_t w, uint32_t h)
{
    for (auto& texture : m_TargetTextures)
        m_RHI->DestroyRHITexture2D(texture);

    m_RHI->DestroyRHIFramebuffer(m_RHIFrameBuffer);

    m_TargetTextures.resize(0);
    m_RHIFrameBuffer = nullptr;

    RHITexture2DCreateDesc texCreateDesc;
    texCreateDesc.PixelFormat = ERHIPixelFormat::PF_R8G8B8A8_UNORM;
    texCreateDesc.Width = w;
    texCreateDesc.Height = h;
    texCreateDesc.NumMips = 1;
    texCreateDesc.NumSamples = 1;

    Ref<RHITexture2D> targetTex = m_RHI->CreateRHITexture2D(texCreateDesc);
    if (!targetTex)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHITexture2D fail");
        return false;
    }

    m_TargetTextures.push_back(targetTex);
    m_RHIFrameBuffer = m_RHI->CreateRHIFramebuffer(w, h, m_RHIRenderPass, m_TargetTextures);
    if (!m_RHIFrameBuffer)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHIFramebuffer fail");
        return false;
    }

    m_Width = w;
    m_Height = h;
    return true;
}

bool TestRenderPass::Draw(Ref<RHICommandBuffer> cmdBuffer)
{
    Ref<RHITexture2D> texture = m_TargetTextures[0];

    m_RHI->CmdPushEvent(cmdBuffer, "TestRenderPass", RHIColor(1, 0, 0, 1));

    m_RHI->CmdPipelineBarrier(
        cmdBuffer,
        RHIPipelineBarrierInfo(
            texture, ERHIAccessFlag::RHI_ACCESS_NONE, ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            ERHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, ERHIImageLayout::RHI_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
            ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            ERHIImageAspectFlag::RHI_IMAGE_ASPECT_COLOR_BIT));

    m_RHI->CmdClearColor(
        cmdBuffer, texture, RHIColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));

    m_RHI->CmdPipelineBarrier(
        cmdBuffer,
        RHIPipelineBarrierInfo(
            texture, ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
            ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT,
            ERHIImageLayout::RHI_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, ERHIImageLayout::RHI_IMAGE_LAYOUT_GENERAL,
            ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            ERHIImageAspectFlag::RHI_IMAGE_ASPECT_COLOR_BIT));

    m_RHI->CmdPopEvent(cmdBuffer);

    return true;
}

void* TestRenderPass::GetTargetImTextureID()
{
    return m_TargetImTextureID;
}

void TestRenderPass::SetColor(std::array<float, 4> color)
{
    m_ClearColor = color;
}
