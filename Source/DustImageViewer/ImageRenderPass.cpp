#include "ImageRenderPass.h"
#include "MediaEngine/Include/Core/Assert.h"
#include "MediaEngine/Include/Application/Application.h"
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

    bool ret = CreateGraphicPipelineAndResources();
    if (!ret)
    {
        IMAGEVIWER_LOG_ERROR("CreateGraphicPipelineAndResources fail");
        return false;
    }

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

    if (!m_Texture)
    {
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
    }
    else
    {
        m_RHI->CmdPipelineBarrier(
            cmdBuffer,
            RHIPipelineBarrierInfo(
                texture, ERHIAccessFlag::RHI_ACCESS_NONE, ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                ERHIImageLayout::RHI_IMAGE_LAYOUT_UNDEFINED, ERHIImageLayout::RHI_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
                ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                ERHIImageAspectFlag::RHI_IMAGE_ASPECT_COLOR_BIT));

        m_RHI->CmdClearColor(cmdBuffer, texture, RHIColor(0, 0, 1, 1));

        m_RHI->CmdPipelineBarrier(
            cmdBuffer, RHIPipelineBarrierInfo(
                           texture, ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                           ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                           ERHIImageLayout::RHI_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                           ERHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                           ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                           ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_VERTEX_INPUT_BIT,
                           ERHIImageAspectFlag::RHI_IMAGE_ASPECT_COLOR_BIT));

        if (m_Texture && !m_UploadTexture)
        {
            m_RHI->CmdCopyBufferToImage(cmdBuffer, m_TextureBuffer, m_Texture);

            m_RHI->CmdPipelineBarrier(
                cmdBuffer, RHIPipelineBarrierInfo(
                               m_Texture, ERHIAccessFlag::RHI_ACCESS_NONE, ERHIAccessFlag::RHI_ACCESS_SHADER_READ_BIT,
                               ERHIImageLayout::RHI_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                               ERHIImageLayout::RHI_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                               ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_TRANSFER_BIT,
                               ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
                               ERHIImageAspectFlag::RHI_IMAGE_ASPECT_COLOR_BIT));

            m_UploadTexture = true;
        }

        RHIRenderPassBeginInfo renderPassBeginInfo;
        renderPassBeginInfo.RenderArea = {0, 0, m_Width, m_Height};
        renderPassBeginInfo.ColorClearValue = {0.1f, 0.2f, 0.3f, 1.f};
        renderPassBeginInfo.RenderPass = m_RHIRenderPass;
        renderPassBeginInfo.Framebuffer = m_RHIFrameBuffer;

        m_RHI->CmdBeginRenderPass(cmdBuffer, renderPassBeginInfo);

        m_RHI->CmdBindGraphicPipeline(cmdBuffer, m_Pipeline);
        RHIViewport viewport = RHIViewport(0, 0, m_Width, m_Height);
        m_RHI->CmdSetViewport(cmdBuffer, viewport);
        RHIScissor scissor = {0, 0, m_Width, m_Height};
        m_RHI->CmdSetScissor(cmdBuffer, scissor);
        m_RHI->CmdBindVertexBuffer(cmdBuffer, m_VertexBuffer);
        m_RHI->CmdBindIndexBuffer(cmdBuffer, m_IndexBuffer);
        m_RHI->CmdBindDescriptorSets(cmdBuffer, m_Pipeline, m_DescriptorSets);
        m_RHI->CmdDrawIndexed(cmdBuffer, 6, 1, 0, 0, 0);

        m_RHI->CmdEndRenderPass(cmdBuffer);

        m_RHI->CmdPipelineBarrier(
            cmdBuffer,
            RHIPipelineBarrierInfo(
                texture, ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_READ_BIT,
                ERHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, ERHIImageLayout::RHI_IMAGE_LAYOUT_GENERAL,
                ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                ERHIImageAspectFlag::RHI_IMAGE_ASPECT_COLOR_BIT));
    }

    m_RHI->CmdPopEvent(cmdBuffer);

    return true;
}

void ImageRenderPass::UpdateImageBuffer(uint32_t w, uint32_t h, ME::Ref<ME::RHIBuffer> buffer)
{
    m_UploadTexture = false;
    m_TextureBuffer = buffer;

    RHITexture2DCreateDesc imageTexCreateDesc;
    imageTexCreateDesc.PixelFormat = ERHIPixelFormat::PF_B8G8R8A8_UNORM;
    imageTexCreateDesc.Width = w;
    imageTexCreateDesc.Height = h;
    imageTexCreateDesc.NumMips = 1;
    imageTexCreateDesc.NumSamples = 1;
    imageTexCreateDesc.Usage = RHI_TEXTURE_USAGE_TRANSFER_DST_BIT | RHI_TEXTURE_USAGE_SAMPLED_BIT;
    imageTexCreateDesc.MemoryProperty = 0;
    m_Texture = m_RHI->CreateRHITexture2D(imageTexCreateDesc);
    if (!m_Texture)
    {
        ME_ASSERT(false, "RHI::CreateRHITexture2D fail");
        return;
    }

    // Update DescriptorSets
    std::vector<RHIWriteDescriptorSet> writeDescSets = {
        RHIWriteDescriptorSet(ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_SAMPLER, 0, 0, m_Sampler),
        RHIWriteDescriptorSet(ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1, 0, m_Texture)};

    m_RHI->UpdateDescriptorSets(m_DescriptorSet, writeDescSets);
}

void* ImageRenderPass::GetTargetImTextureID()
{
    return m_TargetImTextureID;
}

bool ImageRenderPass::CreateGraphicPipelineAndResources()
{
    // Descriptor Set
    RHIDescriptorSetCreateInfo descSetCreateInfo = {
        {0,       ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_SAMPLER, 1, RHI_SHADER_STAGE_FRAGMENT_BIT},
        {1, ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1, RHI_SHADER_STAGE_FRAGMENT_BIT}
    };

    m_DescriptorSet = m_RHI->CreateRHIDescriptorSet(descSetCreateInfo);
    if (!m_DescriptorSet)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateRHIDescriptorSet fail");
        return false;
    }

    m_DescriptorSets = {m_DescriptorSet};

    // Sampler
    RHISamplerCreateInfo samplerInfo;
    m_Sampler = m_RHI->CreateRHISampler(samplerInfo);
    if (!m_Sampler)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateRHISampler fail");
        return false;
    }

    // Shaders
    const std::string resPath = Application::Get().GetResourcePath();
    RHIShaderCreateInfo shaderCreateInfo;
    shaderCreateInfo.Type = ERHIShaderType::Vertex;
    shaderCreateInfo.ShaderFile = resPath + "/Shaders/ImageRenderVS.glsl";
    shaderCreateInfo.EntryName = "main";
    m_VertexShader = m_RHI->CreateRHIShader(shaderCreateInfo);

    shaderCreateInfo.Type = ERHIShaderType::Pixel;
    shaderCreateInfo.ShaderFile = resPath + "/Shaders/ImageRenderPS.glsl";
    shaderCreateInfo.EntryName = "main";
    m_PixelShader = m_RHI->CreateRHIShader(shaderCreateInfo);

    std::vector<Ref<RHIShader>> shaders;
    shaders.push_back(m_VertexShader);
    shaders.push_back(m_PixelShader);

    // VertexInputLayout
    RHIVertexInputLayout vertexInputLayout = {
        {"InPosition", ERHIShaderDataType::Float2, 0},
        {"InTexcoord", ERHIShaderDataType::Float2, 1},
    };

    // Input Assembly
    RHIInputAssemblyInfo inputAssemblyInfo;
    inputAssemblyInfo.PrimitiveTopology = RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    // SetLayout
    std::vector<RHISetLayoutDesc> setLayoutDescs;
    setLayoutDescs.resize(1);
    std::vector<RHISetLayoutBinding> setLayoutBindings;
    setLayoutBindings.resize(1);
    setLayoutBindings[0].Binding = 0;
    setLayoutBindings[0].DescriptorType = ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    setLayoutBindings[0].ShaderStage = ERHIShaderStage::RHI_SHADER_STAGE_FRAGMENT_BIT;
    setLayoutDescs[0].SetLayoutBindings = setLayoutBindings;

    RHIGraphicPipelineCreateInfo graphicPipelineCreateInfo;
    graphicPipelineCreateInfo.Shaders = shaders;
    graphicPipelineCreateInfo.VertexInputLayout = vertexInputLayout;
    graphicPipelineCreateInfo.InputAssemblyInfo = inputAssemblyInfo;
    graphicPipelineCreateInfo.RenderPass = m_RHIRenderPass;
    graphicPipelineCreateInfo.SetLayoutDescs = setLayoutDescs;
    graphicPipelineCreateInfo.DescriptorSet = m_DescriptorSets;

    m_Pipeline = m_RHI->CreateGraphicPipeline(graphicPipelineCreateInfo);
    if (!m_Pipeline)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateGraphicPipeline fail");
        return false;
    }

    // Vertex/Index Buffer
    Vertex vertexDatas[4] = {
        { {-0.5, 0.5}, {0, 1}},
        {  {0.5, 0.5}, {1, 1}},
        { {0.5, -0.5}, {1, 0}},
        {{-0.5, -0.5}, {0, 0}},
    };

    RHIBufferCreateDesc bufferDesc;
    bufferDesc.Usage = RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferDesc.MemoryProperty = RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
    bufferDesc.BufferSize = sizeof(vertexDatas);
    bufferDesc.Data = vertexDatas;
    m_VertexBuffer = m_RHI->CreateRHIBuffer(bufferDesc);
    if (!m_VertexBuffer)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateRHIBuffer fail");
        return false;
    }

    Index indexData[2] = {
        {0, 1, 2},
        {0, 2, 3},
    };

    bufferDesc.Usage = RHI_BUFFER_USAGE_INDEX_BUFFER_BIT;
    bufferDesc.MemoryProperty = RHI_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
    bufferDesc.BufferSize = sizeof(indexData);
    bufferDesc.Data = indexData;
    m_IndexBuffer = m_RHI->CreateRHIBuffer(bufferDesc);
    if (!m_IndexBuffer)
    {
        IMAGEVIWER_LOG_ERROR("RHI::CreateRHIBuffer fail");
        return false;
    }

    return true;
}
