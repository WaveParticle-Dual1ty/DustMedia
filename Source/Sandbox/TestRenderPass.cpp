#include "TestRenderPass.h"
#include "MediaEngine/Include/Core/Assert.h"
#include "MediaEngine/Include/Application/Application.h"
#include "SandboxLog.h"

TestRenderPass::TestRenderPass(Ref<RHI> rhi)
    : FRenderPass(rhi)
{
}

bool TestRenderPass::Initialize(uint32_t w, uint32_t h)
{
    RHIRenderPassCreateDesc desc;
    desc.PixelFormat = ERHIPixelFormat::PF_R8G8B8A8_UNORM;
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
    texCreateDesc.Usage = RHI_TEXTURE_USAGE_COLOR_ATTACHMENT_BIT | RHI_TEXTURE_USAGE_TRANSFER_SRC_BIT |
                          RHI_TEXTURE_USAGE_TRANSFER_DST_BIT | RHI_TEXTURE_USAGE_SAMPLED_BIT;

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

    m_Width = w;
    m_Height = h;

    // Descriptor Set
    RHIDescriptorSetCreateInfo descSetCreateInfo = {
        {0, ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, RHI_SHADER_STAGE_FRAGMENT_BIT}
    };

    m_DescriptorSet = m_RHI->CreateRHIDescriptorSet(descSetCreateInfo);
    if (!m_DescriptorSet)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHIDescriptorSet fail");
        return false;
    }

    // Graphic pipeline
    const std::string resPath = ME::Application::Get().GetResourcePath();
    RHIShaderCreateInfo shaderCreateInfo;
    shaderCreateInfo.Type = ERHIShaderType::Vertex;
    shaderCreateInfo.ShaderFile = resPath + "/Shaders/BasicVertexShader.glsl";
    shaderCreateInfo.EntryName = "main";
    m_VertexShader = m_RHI->CreateRHIShader(shaderCreateInfo);

    shaderCreateInfo.Type = ERHIShaderType::Pixel;
    shaderCreateInfo.ShaderFile = resPath + "/Shaders/BasicPixelShader.glsl";
    shaderCreateInfo.EntryName = "main";
    m_PixelShader = m_RHI->CreateRHIShader(shaderCreateInfo);

    std::vector<Ref<RHIShader>> shaders;
    shaders.push_back(m_VertexShader);
    shaders.push_back(m_PixelShader);

    RHIVertexInputLayout vertexInputLayout = {
        {"InPosition", ERHIShaderDataType::Float4, 0},
        {   "InColor", ERHIShaderDataType::Float4, 1},
        {"InTexcoord", ERHIShaderDataType::Float2, 2},
    };

    // Input Assembly
    RHIInputAssemblyInfo inputAssemblyInfo;
    inputAssemblyInfo.PrimitiveTopology = RHIPrimitiveTopology::RHI_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    // Constant Range
    std::vector<RHIConstantRange> constantRanges;
    RHIConstantRange range;
    range.ShaderStage = ERHIShaderStage::RHI_SHADER_STAGE_FRAGMENT_BIT;
    range.Size = sizeof(ConstantData);
    constantRanges.push_back(range);

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
    graphicPipelineCreateInfo.ConstantRanges = constantRanges;
    graphicPipelineCreateInfo.SetLayoutDescs = setLayoutDescs;

    // Descriptor Set
    m_DescriptorSets = {m_DescriptorSet};
    graphicPipelineCreateInfo.DescriptorSet = m_DescriptorSets;

    m_Pipeline = m_RHI->CreateGraphicPipeline(graphicPipelineCreateInfo);
    if (!m_Pipeline)
    {
        SANDBOX_LOG_ERROR("RHI::CreateGraphicPipeline fail");
        return false;
    }

    // Vertex/Index Buffer
    Vertex vertexDatas[4] = {
        { {-0.5, 0.5, 0, 1}, {1, 0, 0, 1}, {0, 1}},
        {  {0.5, 0.5, 0, 1}, {1, 0, 0, 1}, {1, 1}},
        { {0.5, -0.5, 0, 1}, {1, 0, 0, 1}, {1, 0}},
        {{-0.5, -0.5, 0, 1}, {1, 0, 0, 1}, {0, 0}},
    };

    RHIBufferCreateDesc bufferDesc;
    bufferDesc.Usage = RHI_BUFFER_USAGE_VERTEX_BUFFER_BIT;
    bufferDesc.BufferSize = sizeof(vertexDatas);
    bufferDesc.Data = vertexDatas;
    m_VertexBuffer = m_RHI->CreateRHIBuffer(bufferDesc);
    if (!m_VertexBuffer)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHIBuffer fail");
        return false;
    }

    Index indexData[2] = {
        {0, 1, 2},
        {0, 2, 3},
    };

    bufferDesc.Usage = RHI_BUFFER_USAGE_INDEX_BUFFER_BIT;
    bufferDesc.BufferSize = sizeof(indexData);
    bufferDesc.Data = indexData;
    m_IndexBuffer = m_RHI->CreateRHIBuffer(bufferDesc);
    if (!m_IndexBuffer)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHIBuffer fail");
        return false;
    }

    // create image texture
    std::string imagePath = resPath + "/Images/awesomeface.png";

    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 0);
    ME_ASSERT(data != nullptr, "stbi_load fail");

    RHITexture2DCreateDesc imageTexCreateDesc;
    imageTexCreateDesc.PixelFormat = ERHIPixelFormat::PF_R8G8B8A8_UNORM;
    imageTexCreateDesc.Width = width;
    imageTexCreateDesc.Height = height;
    imageTexCreateDesc.NumMips = 1;
    imageTexCreateDesc.NumSamples = 1;
    imageTexCreateDesc.Usage = RHI_TEXTURE_USAGE_TRANSFER_DST_BIT | RHI_TEXTURE_USAGE_SAMPLED_BIT;
    imageTexCreateDesc.MemoryProperty = 0;
    m_Texture = m_RHI->CreateRHITexture2D(imageTexCreateDesc);
    if (!m_Texture)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHITexture2D fail");
        return false;
    }

    RHIBufferCreateDesc imageBufferDesc;
    imageBufferDesc.Usage = RHI_BUFFER_USAGE_TRANSFER_SRC_BIT;
    imageBufferDesc.BufferSize = width * height * channels;
    imageBufferDesc.Data = data;
    m_ImageBuffer = m_RHI->CreateRHIBuffer(imageBufferDesc);
    if (!m_ImageBuffer)
    {
        SANDBOX_LOG_ERROR("RHI::CreateRHIBuffer fail");
        return false;
    }

    stbi_image_free(data);
    data = nullptr;

    // Update DescriptorSets
    std::vector<RHIWriteDescriptorSet> writeDescSets = {
        {ERHIDescriptorType::RHI_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 0, 0, m_Texture}
    };

    m_RHI->UpdateDescriptorSets(m_DescriptorSet, writeDescSets);

    return true;
}

bool TestRenderPass::Resize(uint32_t w, uint32_t h)
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

    m_Width = w;
    m_Height = h;
    return true;
}

bool TestRenderPass::Draw(Ref<RHICommandBuffer> cmdBuffer)
{
    Ref<RHITexture2D> texture = m_TargetTextures[0];

    m_RHI->CmdPushEvent(cmdBuffer, "TestRenderPass", RHIColor(1, 0, 0, 1));

#if 0
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
#else
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
        cmdBuffer, RHIPipelineBarrierInfo(
                       texture, ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                       ERHIAccessFlag::RHI_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
                       ERHIImageLayout::RHI_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                       ERHIImageLayout::RHI_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
                       ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
                       ERHIPipelineStageFlag::RHI_PIPELINE_STAGE_VERTEX_INPUT_BIT,
                       ERHIImageAspectFlag::RHI_IMAGE_ASPECT_COLOR_BIT));

    if (!m_UploadTexture)
    {
        m_RHI->CmdCopyBufferToImage(cmdBuffer, m_ImageBuffer, m_Texture);

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

    ConstantData constantData;
    constantData.Color = RHIColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
    m_RHI->CmdPushConstants(
        cmdBuffer, m_Pipeline, ERHIShaderStage::RHI_SHADER_STAGE_FRAGMENT_BIT, 0, sizeof(constantData), &constantData);

    //m_RHI->CmdBindDescriptorSets(cmdBuffer, m_Pipeline);
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
#endif

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
