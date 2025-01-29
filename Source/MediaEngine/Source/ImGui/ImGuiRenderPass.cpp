#include "ImGuiRenderPass.h"
#include "ThirdParty/imgui/imgui.h"
#include "ThirdParty/imgui/backends/imgui_impl_vulkan.h"
#include "MediaEngine/Source/Render/Vulkan/VulkanRHIResources.h"
#include "ImGuiLog.h"

namespace ME
{
ImGuiRenderPass::ImGuiRenderPass(Ref<RHI> rhi)
    : FRenderPass(rhi)
{
}

bool ImGuiRenderPass::Initialize(uint32_t w, uint32_t h)
{
    FRenderPass::Initialize(w, h);

    RHIRenderPassCreateDesc desc;
    desc.PixelFormat = ERHIPixelFormat::PF_R8G8B8A8_UNORM;
    m_RHIRenderPass = m_RHI->CreateRHIRenderPass(desc);
    if (!m_RHIRenderPass)
    {
        IMGUI_LOG_ERROR("RHI::CreateRHIRenderPass fail");
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
        IMGUI_LOG_ERROR("RHI::CreateRHITexture2D fail");
        return false;
    }

    m_TargetTextures.push_back(targetTex);
    m_RHIFrameBuffer = m_RHI->CreateRHIFramebuffer(w, h, m_RHIRenderPass, m_TargetTextures);
    if (!m_RHIFrameBuffer)
    {
        IMGUI_LOG_ERROR("RHI::CreateRHIFramebuffer fail");
        return false;
    }

    return true;
}

bool ImGuiRenderPass::Resize(uint32_t w, uint32_t h)
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
        IMGUI_LOG_ERROR("RHI::CreateRHITexture2D fail");
        return false;
    }

    m_TargetTextures.push_back(targetTex);
    m_RHIFrameBuffer = m_RHI->CreateRHIFramebuffer(w, h, m_RHIRenderPass, m_TargetTextures);
    if (!m_RHIFrameBuffer)
    {
        IMGUI_LOG_ERROR("RHI::CreateRHIFramebuffer fail");
        return false;
    }

    m_Width = w;
    m_Height = h;
    return true;
}

bool ImGuiRenderPass::Draw(Ref<RHICommandBuffer> cmdBuffer)
{
    RHIRenderPassBeginInfo renderPassBeginIhfo;
    renderPassBeginIhfo.RenderArea = {0, 0, m_Width, m_Height};
    renderPassBeginIhfo.ColorClearValue = {0.1f, 0.2f, 0.3f, 1.f};
    renderPassBeginIhfo.RenderPass = m_RHIRenderPass;
    renderPassBeginIhfo.Framebuffer = m_RHIFrameBuffer;

    Ref<VulkanRHICommandBuffer> vulkanBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(cmdBuffer);

    m_RHI->CmdBeginRenderPass(cmdBuffer, renderPassBeginIhfo);

    // to do
    ImDrawData* main_draw_data = ImGui::GetDrawData();
    ImGui_ImplVulkan_RenderDrawData(main_draw_data, vulkanBuffer->CommandBuffer);

    m_RHI->CmdEndRenderPass(cmdBuffer);

    return true;
}
}  //namespace ME