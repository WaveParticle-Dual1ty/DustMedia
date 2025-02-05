#include "ImageRenderPass.h"
#include "DustImageViewerLog.h"

using namespace ME;

ImageRenderPass::ImageRenderPass(Ref<RHI> rhi)
    : FRenderPass(rhi)
{
}

bool ImageRenderPass::Initialize(uint32_t w, uint32_t h)
{
    RHIRenderPassCreateDesc desc;
    desc.PixelFormat = ERHIPixelFormat::PF_R8G8B8A8_UNORM;
    m_RHIRenderPass = m_RHI->CreateRHIRenderPass(desc);
    if (!m_RHIRenderPass)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateRHIRenderPass fail");
        return false;
    }

    RHITexture2DCreateDesc texCreateDesc;
    texCreateDesc.PixelFormat = ERHIPixelFormat::PF_R8G8B8A8_UNORM;
    texCreateDesc.Width = w;
    texCreateDesc.Height = h;
    texCreateDesc.NumMips = 1;
    texCreateDesc.NumSamples = 1;
    texCreateDesc.Usage = RHI_TEXTURE_USAGE_COLOR_ATTACHMENT_BIT | RHI_TEXTURE_USAGE_TRANSFER_SRC_BIT |
                          RHI_TEXTURE_USAGE_TRANSFER_DST_BIT | RHI_TEXTURE_USAGE_SAMPLED_BIT;

    Ref<RHITexture2D> targetTex = m_RHI->CreateRHITexture2D(texCreateDesc);
    if (!targetTex)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateRHITexture2D fail");
        return false;
    }

    m_TargetTextures.push_back(targetTex);
    m_RHIFrameBuffer = m_RHI->CreateRHIFramebuffer(w, h, m_RHIRenderPass, m_TargetTextures);
    if (!m_RHIFrameBuffer)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateRHIFramebuffer fail");
        return false;
    }

    m_TargetImTextureID = m_RHI->CreateImTextureID(targetTex);

    m_Width = w;
    m_Height = h;

    return true;
}

bool ImageRenderPass::Resize(uint32_t w, uint32_t h)
{
    m_RHI->DestroyImTextureID(m_TargetImTextureID);
    m_TargetImTextureID = nullptr;

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
    texCreateDesc.Usage = RHI_TEXTURE_USAGE_COLOR_ATTACHMENT_BIT | RHI_TEXTURE_USAGE_TRANSFER_SRC_BIT |
                          RHI_TEXTURE_USAGE_TRANSFER_DST_BIT | RHI_TEXTURE_USAGE_SAMPLED_BIT;

    Ref<RHITexture2D> targetTex = m_RHI->CreateRHITexture2D(texCreateDesc);
    if (!targetTex)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateRHITexture2D fail");
        return false;
    }

    m_TargetTextures.push_back(targetTex);
    m_RHIFrameBuffer = m_RHI->CreateRHIFramebuffer(w, h, m_RHIRenderPass, m_TargetTextures);
    if (!m_RHIFrameBuffer)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateRHIFramebuffer fail");
        return false;
    }

    m_TargetImTextureID = m_RHI->CreateImTextureID(targetTex);

    m_Width = w;
    m_Height = h;

    return true;
}

bool ImageRenderPass::Draw(Ref<RHICommandBuffer> cmdBuffer)
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

    m_RHI->CmdClearColor(cmdBuffer, texture, RHIColor(1, 0, 0, 1));

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

void* ImageRenderPass::GetTargetImTextureID()
{
    return m_TargetImTextureID;
}
