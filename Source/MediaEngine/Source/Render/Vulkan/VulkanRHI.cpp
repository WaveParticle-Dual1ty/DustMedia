#include "VulkanRHI.h"
#include <set>
#include <array>
#include "MediaEngine/Include/Core/Assert.h"
#include "../RenderLog.h"
#include "VulkanRHIUtils.h"
#include "VulkanRHIFramebuffer.h"

namespace ME
{
bool VulkanRHI::Initialize(std::shared_ptr<Window> wnd)
{
    m_Instance = CreateInstance();
    if (m_Instance == VK_NULL_HANDLE)
    {
        RENDER_LOG_ERROR("CreateInstance fail");
        return false;
    }

    GLFWwindow* glfwWnd = (GLFWwindow*)wnd->GetNativeWindow();
    m_Surface = CreateSurface(m_Instance, glfwWnd);
    if (m_Surface == VK_NULL_HANDLE)
    {
        RENDER_LOG_ERROR("CreateSurface fail");
        return false;
    }

    m_PhysicalDevice = SetupPhysicalDevice(m_Instance);
    if (m_PhysicalDevice == VK_NULL_HANDLE)
    {
        RENDER_LOG_ERROR("SetupPhysicalDevice fail");
        return false;
    }

    uint32_t queueFamilyIndexForGraphic = UINT32_MAX;
    uint32_t queueFamilyIndexForPresent = UINT32_MAX;
    uint32_t queueFamilyIndexForCompute = UINT32_MAX;
    bool ret = SetupQueueFamilyIndices(
        m_PhysicalDevice, m_Surface, queueFamilyIndexForGraphic, queueFamilyIndexForPresent,
        queueFamilyIndexForCompute);
    if (!ret)
    {
        RENDER_LOG_ERROR("SetupQueueFamilyIndices fail");
        return false;
    }

    m_Device = CreateDevice(
        m_PhysicalDevice, queueFamilyIndexForGraphic, queueFamilyIndexForPresent, queueFamilyIndexForCompute);
    if (m_Device == VK_NULL_HANDLE)
    {
        RENDER_LOG_ERROR("CreateDevice fail");
        return false;
    }

    VulkanQueue graphicQueue;
    VulkanQueue presentQueue;
    VulkanQueue computeQueue;
    ret = GetQueues(
        m_Device, queueFamilyIndexForGraphic, queueFamilyIndexForPresent, queueFamilyIndexForCompute, graphicQueue,
        presentQueue, computeQueue);
    if (!ret)
    {
        RENDER_LOG_ERROR("GetQueues fail");
        return false;
    }
    m_GraphicQueue = graphicQueue;
    m_PresentQueue = presentQueue;
    m_ComputeQueue = computeQueue;
    ME_ASSERT(m_GraphicQueue.QueueFamilyIndex == m_PresentQueue.QueueFamilyIndex);

    m_RHICommandBuffer = CreateRef<VulkanRHICommandBuffer>();
    ret = CreateCommandResourcesForGraphic(
        m_CommandPool, m_RHICommandBuffer->CommandBuffer, m_FenceForCommandBuffer, m_Device, m_GraphicQueue);

    uint32_t w = wnd->GetWidth();
    uint32_t h = wnd->GetWidth();
    VkExtent2D extend{w, h};
    ret = CreateSwapchainResources(
        m_Swapchain, m_SwapchainTextures, m_ImageAcquiredSemaphores, m_RenderCompleteSemaphores, m_PhysicalDevice,
        m_Device, m_GraphicQueue, m_PresentQueue, m_Surface, extend, m_MinImageCount);
    m_GraphicSemaphoreCnt = (uint32_t)m_ImageAcquiredSemaphores.size();

    m_DescriptorPool = CreateDescriptorPool(m_Device);
    if (m_DescriptorPool == VK_NULL_HANDLE)
    {
        RENDER_LOG_ERROR("CreateDescriptorPool fail");
        return false;
    }

    return true;
}

bool VulkanRHI::Resize(uint32_t width, uint32_t height)
{
    VkResult err = vkDeviceWaitIdle(m_Device);
    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkDeviceWaitIdle fail");
        return false;
    }

    for (auto& sema : m_ImageAcquiredSemaphores)
    {
        vkDestroySemaphore(m_Device, sema, nullptr);
        sema = VK_NULL_HANDLE;
        m_ImageAcquiredSemaphores.resize(0);
    }

    for (auto& sema : m_RenderCompleteSemaphores)
    {
        vkDestroySemaphore(m_Device, sema, nullptr);
        sema = VK_NULL_HANDLE;
        m_RenderCompleteSemaphores.resize(0);
    }

    m_SwapchainTextures.resize(0);

    vkDestroySwapchainKHR(m_Device, m_Swapchain, VK_NULL_HANDLE);
    m_Swapchain = VK_NULL_HANDLE;

    VkExtent2D extend{width, height};
    bool ret = CreateSwapchainResources(
        m_Swapchain, m_SwapchainTextures, m_ImageAcquiredSemaphores, m_RenderCompleteSemaphores, m_PhysicalDevice,
        m_Device, m_GraphicQueue, m_PresentQueue, m_Surface, extend, 2);
    m_GraphicSemaphoreCnt = (uint32_t)m_ImageAcquiredSemaphores.size();

    return true;
}

bool VulkanRHI::PrepareForNextFrame()
{
    VkSemaphore imageAcquiredSemaphore = m_ImageAcquiredSemaphores[m_GraphicSemaphoreIndex];
    VkResult err = vkAcquireNextImageKHR(
        m_Device, m_Swapchain, UINT64_MAX, imageAcquiredSemaphore, VK_NULL_HANDLE, &m_SwapchainFrameIndex);

    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkAcquireNextImageKHR fail");
        return false;
    }

    // wait indefinitely instead of periodically checking
    err = vkWaitForFences(m_Device, 1, &m_FenceForCommandBuffer, VK_TRUE, UINT64_MAX);
    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkWaitForFences fail");
        return false;
    }

    err = vkResetFences(m_Device, 1, &m_FenceForCommandBuffer);
    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkResetFences fail");
        return false;
    }

    err = vkResetCommandBuffer(m_RHICommandBuffer->CommandBuffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkResetCommandBuffer fail");
        return false;
    }

    return true;
}

bool VulkanRHI::SubmmitRenderCommands()
{
    VkSemaphore imageAcquiredSemaphore = m_ImageAcquiredSemaphores[m_GraphicSemaphoreIndex];
    VkSemaphore renderCompleteSemaphore = m_RenderCompleteSemaphores[m_GraphicSemaphoreIndex];

    VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.waitSemaphoreCount = 1;
    info.pWaitSemaphores = &imageAcquiredSemaphore;
    info.pWaitDstStageMask = &wait_stage;
    info.commandBufferCount = 1;
    info.pCommandBuffers = &m_RHICommandBuffer->CommandBuffer;
    info.signalSemaphoreCount = 1;
    info.pSignalSemaphores = &renderCompleteSemaphore;

    VkResult err = vkQueueSubmit(m_GraphicQueue.Queue, 1, &info, m_FenceForCommandBuffer);
    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkQueueSubmit fail");
        return false;
    }

    return true;
}

bool VulkanRHI::Present()
{
    VkSemaphore renderCompleteSemaphore = m_RenderCompleteSemaphores[m_GraphicSemaphoreIndex];
    VkPresentInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info.waitSemaphoreCount = 1;
    info.pWaitSemaphores = &renderCompleteSemaphore;
    info.swapchainCount = 1;
    info.pSwapchains = &m_Swapchain;
    info.pImageIndices = &m_SwapchainFrameIndex;
    VkResult err = vkQueuePresentKHR(m_PresentQueue.Queue, &info);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
    {
        RENDER_LOG_ERROR("vkQueuePresentKHR VK_ERROR_OUT_OF_DATE_KHR or VK_SUBOPTIMAL_KHR");
        return false;
    }

    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkQueuePresentKHR fail");
        return false;
    }

    m_GraphicSemaphoreIndex = (m_GraphicSemaphoreIndex + 1) % m_GraphicSemaphoreCnt;
    return true;
}

Ref<RHICommandBuffer> VulkanRHI::GetCurrentCommandBuffer() const
{
    return m_RHICommandBuffer;
}

Ref<RHITexture2D> VulkanRHI::GetCurrentBackTexture()
{
    Ref<VulkanRHITexture2D> currentTex = m_SwapchainTextures[m_SwapchainFrameIndex];
    return currentTex;
}

Ref<RHITexture2D> VulkanRHI::CreateRHITexture2D(RHITexture2DCreateDesc desc)
{
    Ref<VulkanRHITexture2D> texture = CreateRef<VulkanRHITexture2D>();
    texture->m_PixelFormat = desc.PixelFormat;
    texture->m_Width = desc.Width;
    texture->m_Height = desc.Height;

    VkFormat format = Util::ConvertERHIPixelFormatToVkFormat(desc.PixelFormat);
    texture->m_VKFormat = format;

    // create image
    VkImageCreateInfo imageCreateInfo;
    imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    imageCreateInfo.pNext = nullptr;
    imageCreateInfo.flags = 0;
    imageCreateInfo.imageType = VK_IMAGE_TYPE_2D;
    imageCreateInfo.format = format;
    imageCreateInfo.extent = {desc.Width, desc.Height, 1};
    imageCreateInfo.mipLevels = 1;
    imageCreateInfo.arrayLayers = 1;
    imageCreateInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    imageCreateInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    imageCreateInfo.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    imageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    imageCreateInfo.queueFamilyIndexCount = 0;
    imageCreateInfo.pQueueFamilyIndices = nullptr;
    imageCreateInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    VkResult res = vkCreateImage(m_Device, &imageCreateInfo, nullptr, &texture->m_Image);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateImage fail");
        return nullptr;
    }

    // bind image memeory
    VkMemoryRequirements memRequirement;
    vkGetImageMemoryRequirements(m_Device, texture->m_Image, &memRequirement);

    VkMemoryAllocateInfo memAlloInfo;
    memAlloInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memAlloInfo.pNext = nullptr;
    memAlloInfo.allocationSize = memRequirement.size;
    memAlloInfo.memoryTypeIndex = 0;

    res = vkAllocateMemory(m_Device, &memAlloInfo, nullptr, &texture->m_DeviceMem);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkAllocateMemory fail");
        return nullptr;
    }

    res = vkBindImageMemory(m_Device, texture->m_Image, texture->m_DeviceMem, 0);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkBindImageMemory fail");
        return nullptr;
    }

    // create image view
    VkComponentMapping componentMapping;
    componentMapping.r = VK_COMPONENT_SWIZZLE_R;
    componentMapping.g = VK_COMPONENT_SWIZZLE_G;
    componentMapping.b = VK_COMPONENT_SWIZZLE_B;
    componentMapping.a = VK_COMPONENT_SWIZZLE_A;

    VkImageSubresourceRange imageSubresourceRange;
    imageSubresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageSubresourceRange.baseMipLevel = 0;
    imageSubresourceRange.levelCount = 1;
    imageSubresourceRange.baseArrayLayer = 0;
    imageSubresourceRange.layerCount = 1;

    VkImageViewCreateInfo imageViewCreateInfo;
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.pNext = nullptr;
    imageViewCreateInfo.flags = 0;
    imageViewCreateInfo.image = texture->m_Image;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.format = format;
    imageViewCreateInfo.components = componentMapping;
    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
    imageViewCreateInfo.subresourceRange.layerCount = 1;

    res = vkCreateImageView(m_Device, &imageViewCreateInfo, nullptr, &texture->m_ImageView);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateImageView fail");
        return nullptr;
    }

    return texture;
}

Ref<RHIRenderPass> VulkanRHI::CreateRHIRenderPass(RHIRenderPassCreateDesc desc)
{
    VkAttachmentDescription attachmentDesc;
    attachmentDesc.flags = 0;
    attachmentDesc.format = VK_FORMAT_R8G8B8A8_UNORM;
    attachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;
    attachmentDesc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachmentDesc.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachmentDesc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachmentDesc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachmentDesc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachmentDesc.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorAttachRef;
    colorAttachRef.attachment = 0;
    colorAttachRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpassDesc;
    subpassDesc.flags = 0;
    subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDesc.inputAttachmentCount = 0;
    subpassDesc.pInputAttachments = nullptr;
    subpassDesc.colorAttachmentCount = 1;
    subpassDesc.pColorAttachments = &colorAttachRef;
    subpassDesc.pResolveAttachments = nullptr;
    subpassDesc.pDepthStencilAttachment = nullptr;
    subpassDesc.preserveAttachmentCount = 0;
    subpassDesc.pPreserveAttachments = nullptr;

    VkRenderPassCreateInfo renderPassCreateInfo;
    renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.pNext = nullptr;
    renderPassCreateInfo.flags = 0;
    renderPassCreateInfo.attachmentCount = 1;
    renderPassCreateInfo.pAttachments = &attachmentDesc;
    renderPassCreateInfo.subpassCount = 1;
    renderPassCreateInfo.pSubpasses = &subpassDesc;
    renderPassCreateInfo.dependencyCount = 0;
    renderPassCreateInfo.pDependencies = nullptr;

    Ref<VulkanRHIRenderPass> renderPass = CreateRef<VulkanRHIRenderPass>();
    VkResult res = vkCreateRenderPass(m_Device, &renderPassCreateInfo, nullptr, &renderPass->RenderPass);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateRenderPass fail");
        return nullptr;
    }

    return renderPass;
}

Ref<RHIFramebuffer> VulkanRHI::CreateRHIFramebuffer(
    uint32_t width,
    uint32_t height,
    Ref<RHIRenderPass> renderPass,
    std::vector<Ref<RHITexture2D>>& textures)
{
    ME_ASSERT(textures.size() > 0, "No textures");

    Ref<VulkanRHIFrameBuffer> framebuffer = CreateRef<VulkanRHIFrameBuffer>();
    framebuffer->m_Width = width;
    framebuffer->m_Height = height;
    framebuffer->m_RenderPass = renderPass;
    framebuffer->m_Textures = textures;

    Ref<VulkanRHIRenderPass> vulkanRenderPass = std::dynamic_pointer_cast<VulkanRHIRenderPass>(renderPass);

    std::vector<VkImageView> imageViews;
    imageViews.resize(textures.size());
    for (size_t i = 0; i < textures.size(); ++i)
    {
        Ref<VulkanRHITexture2D> vulkanTex = std::dynamic_pointer_cast<VulkanRHITexture2D>(textures[i]);
        imageViews[i] = vulkanTex->m_ImageView;
    }

    VkFramebufferCreateInfo framebufferCreateInfo;
    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.pNext = nullptr;
    framebufferCreateInfo.flags = 0;
    framebufferCreateInfo.renderPass = vulkanRenderPass->RenderPass;
    framebufferCreateInfo.attachmentCount = imageViews.size();
    framebufferCreateInfo.pAttachments = imageViews.data();
    framebufferCreateInfo.width = width;
    framebufferCreateInfo.height = height;
    framebufferCreateInfo.layers = 1;

    VkResult res = vkCreateFramebuffer(m_Device, &framebufferCreateInfo, nullptr, &framebuffer->m_Framebuffer);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateFramebuffer fail");
        return nullptr;
    }

    return framebuffer;
}

void VulkanRHI::DestroyRHITexture2D(Ref<RHITexture2D> texture)
{
    Ref<VulkanRHITexture2D> vulkanTexture = std::dynamic_pointer_cast<VulkanRHITexture2D>(texture);
    vulkanTexture->m_PixelFormat = ERHIPixelFormat::PF_Unknown;
    vulkanTexture->m_Width = 0;
    vulkanTexture->m_Height = 0;
    vulkanTexture->m_VKFormat = VK_FORMAT_UNDEFINED;

    vkDestroyImageView(m_Device, vulkanTexture->m_ImageView, nullptr);
    vulkanTexture->m_ImageView = VK_NULL_HANDLE;
    vkFreeMemory(m_Device, vulkanTexture->m_DeviceMem, nullptr);
    vulkanTexture->m_DeviceMem = VK_NULL_HANDLE;
    vkDestroyImage(m_Device, vulkanTexture->m_Image, nullptr);
    vulkanTexture->m_Image = VK_NULL_HANDLE;
}

void VulkanRHI::DestroyRHIRenderPass(Ref<RHIRenderPass> renderPass)
{
    Ref<VulkanRHIRenderPass> vulkanRenderPass = std::dynamic_pointer_cast<VulkanRHIRenderPass>(renderPass);
    vkDestroyRenderPass(m_Device, vulkanRenderPass->RenderPass, nullptr);
    vulkanRenderPass->RenderPass = VK_NULL_HANDLE;
}

void VulkanRHI::DestroyRHIFramebuffer(Ref<RHIFramebuffer> framebuffer)
{
    Ref<VulkanRHIFrameBuffer> vulkanFramebuffer = std::dynamic_pointer_cast<VulkanRHIFrameBuffer>(framebuffer);
    vulkanFramebuffer->m_Width = 0;
    vulkanFramebuffer->m_Height = 0;
    vulkanFramebuffer->m_RenderPass = nullptr;
    vulkanFramebuffer->m_Textures.resize(0);

    vkDestroyFramebuffer(m_Device, vulkanFramebuffer->m_Framebuffer, nullptr);
    vulkanFramebuffer->m_Framebuffer = VK_NULL_HANDLE;
}

bool VulkanRHI::BeginCommandBuffer(Ref<RHICommandBuffer> cmdBuffer)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(cmdBuffer);

    VkCommandBufferBeginInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
    VkResult err = vkBeginCommandBuffer(vulkanCmdBuffer->CommandBuffer, &info);
    if (err != VK_SUCCESS)
    {
        ME_ASSERT(false, "vkBeginCommandBuffer fail");
        return false;
    }

    return true;
}

bool VulkanRHI::EndCommandBuffer(Ref<RHICommandBuffer> cmdBuffer)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(cmdBuffer);

    VkResult err = vkEndCommandBuffer(vulkanCmdBuffer->CommandBuffer);
    if (err != VK_SUCCESS)
    {
        ME_ASSERT(false, "vkBeginCommandBuffer fail");
        return false;
    }

    return true;
}

void VulkanRHI::CmdBeginRenderPass(Ref<RHICommandBuffer> cmdBuffer, RHIRenderPassBeginInfo beginIhfo)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(cmdBuffer);
    Ref<VulkanRHIRenderPass> renderPass = std::dynamic_pointer_cast<VulkanRHIRenderPass>(beginIhfo.RenderPass);
    Ref<VulkanRHIFrameBuffer> framebuffer = std::dynamic_pointer_cast<VulkanRHIFrameBuffer>(beginIhfo.Framebuffer);

    VkRect2D renderArea;
    renderArea.offset = {beginIhfo.RenderArea.OffsetX, beginIhfo.RenderArea.OffsetY};
    renderArea.extent = {beginIhfo.RenderArea.Width, beginIhfo.RenderArea.Height};

    VkClearValue clearValue;
    clearValue.color.float32[0] = beginIhfo.ColorClearValue.R;
    clearValue.color.float32[1] = beginIhfo.ColorClearValue.G;
    clearValue.color.float32[2] = beginIhfo.ColorClearValue.B;
    clearValue.color.float32[3] = beginIhfo.ColorClearValue.A;

    VkRenderPassBeginInfo renderPassBeginInfo;
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.pNext = nullptr;
    renderPassBeginInfo.renderPass = renderPass->RenderPass;
    renderPassBeginInfo.framebuffer = framebuffer->m_Framebuffer;
    renderPassBeginInfo.renderArea = renderArea;
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = &clearValue;

    vkCmdBeginRenderPass(vulkanCmdBuffer->CommandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void VulkanRHI::CmdEndRenderPass(Ref<RHICommandBuffer> cmdBuffer)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(cmdBuffer);
    vkCmdEndRenderPass(vulkanCmdBuffer->CommandBuffer);
}

void VulkanRHI::CmdClearColor(Ref<RHICommandBuffer> cmdBuffer, Ref<RHITexture2D> texture, RHIColor color)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(cmdBuffer);
    Ref<VulkanRHITexture2D> vulkanTexture = std::dynamic_pointer_cast<VulkanRHITexture2D>(texture);

    VkClearColorValue clearColor;
    clearColor.float32[0] = color.R;
    clearColor.float32[1] = color.G;
    clearColor.float32[2] = color.B;
    clearColor.float32[3] = color.A;

    VkImageSubresourceRange subresRange;
    subresRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresRange.baseMipLevel = 0;
    subresRange.levelCount = 1;
    subresRange.baseArrayLayer = 0;
    subresRange.layerCount = 1;

    vkCmdClearColorImage(
        vulkanCmdBuffer->CommandBuffer, vulkanTexture->m_Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clearColor, 1,
        &subresRange);
}

void VulkanRHI::CmdPipelineBarrier(Ref<RHICommandBuffer> cmdBuffer, RHIPipelineBarrierInfo barrierInfo)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(cmdBuffer);

    if (barrierInfo.Type == RHIPipelineBarrierInfo::EType::Texture)
    {
        Ref<VulkanRHITexture2D> texture = std::dynamic_pointer_cast<VulkanRHITexture2D>(barrierInfo.Texture);

        VkImageMemoryBarrier barrier;
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.pNext = nullptr;
        barrier.srcAccessMask = Util::ConvertERHIAccessFlagToVkAccessFlags(barrierInfo.SrcAcessFlag);
        barrier.dstAccessMask = Util::ConvertERHIAccessFlagToVkAccessFlags(barrierInfo.DstAcessFlag);
        barrier.oldLayout = Util::ConvertERHIImageLayoutToVkImageLayout(barrierInfo.OldLayout);
        barrier.newLayout = Util::ConvertERHIImageLayoutToVkImageLayout(barrierInfo.NewLayout);
        barrier.srcQueueFamilyIndex = barrierInfo.SrcQueueFamilyIndex;
        barrier.dstQueueFamilyIndex = barrierInfo.DstQueueFamilyIndex;
        barrier.image = texture->m_Image;
        barrier.subresourceRange.aspectMask =
            Util::ConvertERHIImageAspectFlagToVkImageAspectFlags(barrierInfo.AspectMask);
        barrier.subresourceRange.baseMipLevel = barrierInfo.BaseMipLevel;
        barrier.subresourceRange.levelCount = barrierInfo.LevelCount;
        barrier.subresourceRange.baseArrayLayer = barrierInfo.BaseArrayLayer;
        barrier.subresourceRange.layerCount = barrierInfo.LayerCount;

        VkPipelineStageFlags srcPipelineStage =
            Util::ConvertERHIPipelineStageFlagToVkPipelineStageFlags(barrierInfo.SrcPipelineStage);
        VkPipelineStageFlags dstPipelineStage =
            Util::ConvertERHIPipelineStageFlagToVkPipelineStageFlags(barrierInfo.DstPipelineStage);

        vkCmdPipelineBarrier(
            vulkanCmdBuffer->CommandBuffer, srcPipelineStage, dstPipelineStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
    }
    else
    {
        ME_ASSERT(false, "Not support pipeline barrier type now");
    }
}

void VulkanRHI::CmdCopyTexture(Ref<RHICommandBuffer> cmdBuffer, Ref<RHITexture2D> src, Ref<RHITexture2D> dst)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(cmdBuffer);
    Ref<VulkanRHITexture2D> srcTex = std::dynamic_pointer_cast<VulkanRHITexture2D>(src);
    Ref<VulkanRHITexture2D> dstTex = std::dynamic_pointer_cast<VulkanRHITexture2D>(dst);

    VkImageCopy imageCopy;
    imageCopy.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageCopy.srcSubresource.mipLevel = 0;
    imageCopy.srcSubresource.baseArrayLayer = 0;
    imageCopy.srcSubresource.layerCount = 1;
    imageCopy.srcOffset = {0, 0, 0};
    imageCopy.dstSubresource = imageCopy.srcSubresource;
    imageCopy.dstOffset = {0, 0, 0};
    imageCopy.extent = {srcTex->GetWidth(), srcTex->GetHeight(), 1};

    vkCmdCopyImage(
        vulkanCmdBuffer->CommandBuffer, srcTex->m_Image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dstTex->m_Image,
        VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &imageCopy);
}

VkInstance VulkanRHI::GetInstance()
{
    return m_Instance;
}

VkPhysicalDevice VulkanRHI::GetPhysicalDevice()
{
    return m_PhysicalDevice;
}

VkDevice VulkanRHI::GetDevice()
{
    return m_Device;
}

VulkanRHI::VulkanQueue VulkanRHI::GetGraphicQueue()
{
    return m_GraphicQueue;
}

VkDescriptorPool VulkanRHI::GetDescriptorPool()
{
    return m_DescriptorPool;
}

uint32_t VulkanRHI::GetMinImageCount()
{
    return m_MinImageCount;
}

uint32_t VulkanRHI::GetBackImageCount()
{
    return (uint32_t)m_SwapchainTextures.size();
}

bool VulkanRHI::IsExtensionAvailable(const std::vector<VkExtensionProperties>& properties, const char* extension)
{
    for (const auto& p : properties)
    {
        if (strcmp(p.extensionName, extension) == 0)
            return true;
    }

    return false;
}

VkInstance VulkanRHI::CreateInstance()
{
    uint32_t instanceExtensionCnt = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCnt, nullptr);
    std::vector<VkExtensionProperties> instanceExtensionProperties(instanceExtensionCnt);
    vkEnumerateInstanceExtensionProperties(nullptr, &instanceExtensionCnt, instanceExtensionProperties.data());

    // check glfw required instance extensions
    uint32_t glfwRequiredExtensionCnt = 0;
    auto glfwRequiredExtensions = glfwGetRequiredInstanceExtensions(&glfwRequiredExtensionCnt);

    std::set<const char*> toEnableExtensionsSet;
    for (uint32_t i = 0; i < glfwRequiredExtensionCnt; ++i)
    {
        const char* extension = glfwRequiredExtensions[i];
        if (IsExtensionAvailable(instanceExtensionProperties, extension))
        {
            toEnableExtensionsSet.insert(extension);
        }
        else
        {
            RENDER_LOG_ERROR("Not support extension: {}", extension);
            return VK_NULL_HANDLE;
        }
    }

    // check other required instance extensions
    bool enableVulkanDebug = true;
    if (enableVulkanDebug)
    {
        if (IsExtensionAvailable(instanceExtensionProperties, VK_EXT_DEBUG_REPORT_EXTENSION_NAME))
            toEnableExtensionsSet.insert(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
        if (IsExtensionAvailable(instanceExtensionProperties, VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
            toEnableExtensionsSet.insert(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    // create instance
    std::vector<const char*> toEnableExtensions;
    for (auto& extension : toEnableExtensionsSet)
        toEnableExtensions.push_back(extension);

    RENDER_LOG_INFO("Enable Instance Extensions:");
    for (auto& extension : toEnableExtensions)
        RENDER_LOG_INFO("\t{}", extension);

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr;
    appInfo.pApplicationName = "Application";
    appInfo.applicationVersion = 1;
    appInfo.pEngineName = "Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

    VkInstanceCreateInfo instanceCreateInfo;
    instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceCreateInfo.pNext = nullptr;
    instanceCreateInfo.flags = 0;
    instanceCreateInfo.pApplicationInfo = &appInfo;
    instanceCreateInfo.enabledLayerCount = 0;
    instanceCreateInfo.ppEnabledExtensionNames = nullptr;
    instanceCreateInfo.enabledExtensionCount = (uint32_t)toEnableExtensions.size();
    instanceCreateInfo.ppEnabledExtensionNames = toEnableExtensions.data();

    VkInstance instance = VK_NULL_HANDLE;
    VkResult res = vkCreateInstance(&instanceCreateInfo, nullptr, &instance);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateInstance fail");
        return VK_NULL_HANDLE;
    }

    return instance;
}

VkSurfaceKHR VulkanRHI::CreateSurface(VkInstance instance, GLFWwindow* wnd)
{
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkResult res = glfwCreateWindowSurface(instance, wnd, nullptr, &surface);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("glfwCreateWindowSurface fail");
        return VK_NULL_HANDLE;
    }

    return surface;
}

VkPhysicalDevice VulkanRHI::SetupPhysicalDevice(VkInstance instance)
{
    uint32_t physicalDeviceCnt = 0;
    VkResult res = vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCnt, nullptr);
    if (res != VK_SUCCESS || physicalDeviceCnt == 0)
    {
        RENDER_LOG_ERROR("vkEnumeratePhysicalDevices fail");
        return VK_NULL_HANDLE;
    }

    std::vector<VkPhysicalDevice> physicalDevices;
    physicalDevices.resize(physicalDeviceCnt);
    vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCnt, &physicalDevices[0]);

    VkPhysicalDevice physicalDevice = physicalDevices[0];

    VkPhysicalDeviceProperties deviceProperty;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperty);
    RENDER_LOG_INFO("Gpu Device: {}", deviceProperty.deviceName);

    return physicalDevice;
}

bool VulkanRHI::SetupQueueFamilyIndices(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface,
    uint32_t& queueFamilyIndexForGraphic,
    uint32_t& queueFamilyIndexForPresent,
    uint32_t& queueFamilyIndexForCompute)
{
    uint32_t queueCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueCount, queueFamilies.data());

    queueFamilyIndexForGraphic = UINT32_MAX;
    queueFamilyIndexForPresent = UINT32_MAX;
    queueFamilyIndexForCompute = UINT32_MAX;
    for (uint32_t i = 0; i < queueCount; ++i)
    {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            queueFamilyIndexForGraphic = i;

        if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
            queueFamilyIndexForCompute = i;

        VkBool32 ret = vkGetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, i);
        if (ret == VK_TRUE)
        {
            VkBool32 isSupport = VK_FALSE;
            VkResult err = vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &isSupport);
            if (err == VK_SUCCESS && isSupport == VK_TRUE)
            {
                queueFamilyIndexForPresent = i;
            }
        }

        if (queueFamilyIndexForGraphic != UINT32_MAX && queueFamilyIndexForPresent != UINT32_MAX &&
            queueFamilyIndexForCompute != UINT32_MAX)
        {
            return true;
        }
    }

    return false;
}

VkDevice VulkanRHI::CreateDevice(
    VkPhysicalDevice physicalDevice,
    uint32_t queueFamilyIndexForGraphic,
    uint32_t queueFamilyIndexForPresent,
    uint32_t queueFamilyIndexForCompute)
{
    std::set<uint32_t> queueFamilies = {
        queueFamilyIndexForGraphic, queueFamilyIndexForPresent, queueFamilyIndexForCompute};

    std::vector<VkDeviceQueueCreateInfo> deviceQueueCreateInfos;
    for (uint32_t queueFamilieIndex : queueFamilies)
    {
        VkDeviceQueueCreateInfo deviceQueueCreateInfo;
        deviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        deviceQueueCreateInfo.pNext = nullptr;
        deviceQueueCreateInfo.flags = 0;
        deviceQueueCreateInfo.queueFamilyIndex = queueFamilieIndex;
        deviceQueueCreateInfo.queueCount = 1;
        float queuePriority = 1.0f;
        deviceQueueCreateInfo.pQueuePriorities = &queuePriority;
        deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
    }

    uint32_t devicePropertiesCnt = 0;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &devicePropertiesCnt, nullptr);
    std::vector<VkExtensionProperties> deviceProperties(devicePropertiesCnt);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &devicePropertiesCnt, deviceProperties.data());

    std::vector<const char*> enableExtensions = {
        "VK_KHR_swapchain",
        //"VK_KHR_pipeline_library",
        //"VK_EXT_graphics_pipeline_library",
    };

    for (auto& extension : enableExtensions)
    {
        if (!IsExtensionAvailable(deviceProperties, extension))
        {
            RENDER_LOG_ERROR("Not support extension: {}", extension);
            return VK_NULL_HANDLE;
        }
    }

    RENDER_LOG_INFO("Enable Device Extensions:");
    for (auto& extension : enableExtensions)
        RENDER_LOG_INFO("\t{}", extension);

    VkPhysicalDeviceFeatures supportedFeatures;
    vkGetPhysicalDeviceFeatures(physicalDevice, &supportedFeatures);

    VkDeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pNext = nullptr;
    deviceCreateInfo.flags = 0;
    deviceCreateInfo.queueCreateInfoCount = deviceQueueCreateInfos.size();
    deviceCreateInfo.pQueueCreateInfos = deviceQueueCreateInfos.data();
    deviceCreateInfo.enabledLayerCount = 0;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;
    deviceCreateInfo.enabledExtensionCount = enableExtensions.size();
    deviceCreateInfo.ppEnabledExtensionNames = enableExtensions.data();
    deviceCreateInfo.pEnabledFeatures = &supportedFeatures;

    VkDevice device = VK_NULL_HANDLE;
    VkResult result = vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, &device);
    if (result != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateDevice fail");
        return VK_NULL_HANDLE;
    }

    return device;
}

bool VulkanRHI::GetQueues(
    VkDevice device,
    uint32_t queueFamilyIndexForGraphic,
    uint32_t queueFamilyIndexForPresent,
    uint32_t queueFamilyIndexForCompute,
    VulkanQueue& graphicQueue,
    VulkanQueue& presentQueue,
    VulkanQueue& computeQueue)
{
    VkQueue queueGraphic = VK_NULL_HANDLE;
    vkGetDeviceQueue(device, queueFamilyIndexForGraphic, 0, &queueGraphic);
    graphicQueue.Queue = queueGraphic;
    graphicQueue.QueueFamilyIndex = queueFamilyIndexForGraphic;

    VkQueue queuePresent = VK_NULL_HANDLE;
    vkGetDeviceQueue(device, queueFamilyIndexForPresent, 0, &queuePresent);
    presentQueue.Queue = queuePresent;
    presentQueue.QueueFamilyIndex = queueFamilyIndexForPresent;

    VkQueue queueCompute = VK_NULL_HANDLE;
    vkGetDeviceQueue(device, queueFamilyIndexForCompute, 0, &queueCompute);
    computeQueue.Queue = queuePresent;
    computeQueue.QueueFamilyIndex = queueFamilyIndexForCompute;

    return true;
}

bool VulkanRHI::CreateCommandResourcesForGraphic(
    VkCommandPool& commandPool,
    VkCommandBuffer& commandBuffer,
    VkFence& fenceForBuffer,
    VkDevice device,
    VulkanQueue graphicQueue)
{
    VkCommandPoolCreateInfo commandPoolCreateInfo = {};
    commandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    commandPoolCreateInfo.queueFamilyIndex = graphicQueue.QueueFamilyIndex;
    VkCommandPool pool = VK_NULL_HANDLE;
    VkResult err = vkCreateCommandPool(device, &commandPoolCreateInfo, nullptr, &pool);
    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateCommandPool fail");
        return false;
    }

    VkCommandBufferAllocateInfo commandBufferAllocInfo = {};
    commandBufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocInfo.commandPool = pool;
    commandBufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocInfo.commandBufferCount = 1;
    VkCommandBuffer buffer = VK_NULL_HANDLE;
    err = vkAllocateCommandBuffers(device, &commandBufferAllocInfo, &buffer);
    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateCommandPool fail");
        return false;
    }

    VkFenceCreateInfo fenceCreateInfo = {};
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    VkFence fence = VK_NULL_HANDLE;
    err = vkCreateFence(device, &fenceCreateInfo, nullptr, &fence);
    if (err != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateCommandPool fail");
        return false;
    }

    commandPool = pool;
    commandBuffer = buffer;
    fenceForBuffer = fence;
    return true;
}

std::vector<VkSurfaceFormatKHR> VulkanRHI::GetSupportSurfaceFormats(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR surface)
{
    uint32_t surfaceFormatCnt;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCnt, nullptr);
    std::vector<VkSurfaceFormatKHR> surfaceFormats;
    surfaceFormats.resize(surfaceFormatCnt);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCnt, surfaceFormats.data());

    std::vector<VkSurfaceFormatKHR> res;
    for (auto& surfaceFormat : surfaceFormats)
    {
        VkSurfaceFormatKHR tmp;
        tmp.format = surfaceFormat.format;
        tmp.colorSpace = surfaceFormat.colorSpace;
        res.push_back(tmp);
    }

    return res;
}

std::vector<VkPresentModeKHR> VulkanRHI::GetSupportPresentModes(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    uint32_t presentModeCnt = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCnt, nullptr);
    std::vector<VkPresentModeKHR> presentModes;
    presentModes.resize(presentModeCnt);
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCnt, presentModes.data());

    std::vector<VkPresentModeKHR> res;
    for (auto& presentMode : presentModes)
    {
        res.push_back(presentMode);
    }

    return res;
}

bool VulkanRHI::CreateSwapchainResources(
    VkSwapchainKHR& swapchain,
    std::vector<Ref<VulkanRHITexture2D>>& swapchainTextures,
    std::vector<VkSemaphore>& imageAcquiredSemaphores,
    std::vector<VkSemaphore>& renderCompleteSemaphores,
    VkPhysicalDevice physicalDevie,
    VkDevice device,
    VulkanQueue graphicQueue,
    VulkanQueue presentQueue,
    VkSurfaceKHR surface,
    VkExtent2D extend,
    uint32_t minImageCount)
{
    auto supportSurfaceFormats = GetSupportSurfaceFormats(physicalDevie, surface);
    auto supportPresentModes = GetSupportPresentModes(physicalDevie, surface);
    ME_ASSERT(supportSurfaceFormats.size() != 0, "No support surface format");
    ME_ASSERT(supportPresentModes.size() != 0, "No support present mode");
    VkSurfaceFormatKHR surfaceFormat = supportSurfaceFormats[0];
    for (auto format : supportSurfaceFormats)
    {
        if (format.format == VK_FORMAT_R8G8B8A8_UNORM)
            surfaceFormat = format;
    }

    VkPresentModeKHR presentMode = supportPresentModes[0];

    // create swapchain
    VkSwapchainCreateInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    info.surface = surface;
    info.minImageCount = minImageCount;
    info.imageFormat = surfaceFormat.format;
    info.imageColorSpace = surfaceFormat.colorSpace;
    info.imageExtent = extend;
    info.imageArrayLayers = 1;
    info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;

    if (graphicQueue.QueueFamilyIndex != presentQueue.QueueFamilyIndex)
    {
        std::array<uint32_t, 2> queueFamilyIndices;
        queueFamilyIndices[0] = graphicQueue.QueueFamilyIndex;
        queueFamilyIndices[1] = presentQueue.QueueFamilyIndex;
        info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        info.queueFamilyIndexCount = 2;
        info.pQueueFamilyIndices = queueFamilyIndices.data();
    }
    else
    {
        info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    }

    info.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    info.presentMode = presentMode;
    info.clipped = VK_TRUE;
    info.oldSwapchain = VK_NULL_HANDLE;

    VkSurfaceCapabilitiesKHR surfaceCapability;
    VkResult res = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevie, surface, &surfaceCapability);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkGetPhysicalDeviceSurfaceCapabilitiesKHR fail");
        return false;
    }

    if (info.minImageCount < surfaceCapability.minImageCount)
        info.minImageCount = surfaceCapability.minImageCount;
    else if (surfaceCapability.maxImageCount != 0 && info.minImageCount > surfaceCapability.maxImageCount)
        info.minImageCount = surfaceCapability.maxImageCount;

    if (surfaceCapability.currentExtent.width == 0xffffffff)
    {
        info.imageExtent = extend;
    }
    else
    {
        info.imageExtent = surfaceCapability.currentExtent;
    }

    res = vkCreateSwapchainKHR(device, &info, nullptr, &swapchain);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateSwapchainKHR fail");
        return false;
    }

    // get swapchain images
    uint32_t swapchainImageCount = 0;
    res = vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, nullptr);
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkGetSwapchainImagesKHR fail");
        return false;
    }

    std::vector<VkImage> swapchainImages;
    swapchainImages.resize(swapchainImageCount);
    res = vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages.data());
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkGetSwapchainImagesKHR fail");
        return false;
    }

    swapchainTextures.clear();
    swapchainTextures.resize(swapchainImageCount);
    for (size_t i = 0; i < swapchainImages.size(); ++i)
    {
        Ref<VulkanRHITexture2D> texture = CreateRef<VulkanRHITexture2D>();
        texture->m_PixelFormat = ERHIPixelFormat::PF_Unknown;
        texture->m_Width = info.imageExtent.width;
        texture->m_Height = info.imageExtent.height;
        texture->m_VKFormat = info.imageFormat;
        texture->m_Image = swapchainImages[i];
        swapchainTextures[i] = texture;
    }

    // create semaphore
    size_t graphicSemaphoreCnt = swapchainImages.size() + 1;
    imageAcquiredSemaphores.resize(graphicSemaphoreCnt);
    renderCompleteSemaphores.resize(graphicSemaphoreCnt);

    for (uint32_t i = 0; i < graphicSemaphoreCnt; i++)
    {
        VkSemaphoreCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        VkResult err = vkCreateSemaphore(m_Device, &info, nullptr, &imageAcquiredSemaphores[i]);
        if (err != VK_SUCCESS)
        {
            RENDER_LOG_ERROR("vkCreateSemaphore fail");
            return false;
        }

        err = vkCreateSemaphore(m_Device, &info, nullptr, &renderCompleteSemaphores[i]);
        if (err != VK_SUCCESS)
        {
            RENDER_LOG_ERROR("vkCreateSemaphore fail");
            return false;
        }
    }

    return true;
}

VkDescriptorPool VulkanRHI::CreateDescriptorPool(VkDevice device)
{
    std::array<VkDescriptorPoolSize, 1> poolSizes = {
        {VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1}
    };

    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo;
    descriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descriptorPoolCreateInfo.pNext = nullptr;
    descriptorPoolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
    descriptorPoolCreateInfo.maxSets = 1;
    descriptorPoolCreateInfo.poolSizeCount = poolSizes.size();
    descriptorPoolCreateInfo.pPoolSizes = poolSizes.data();

    VkDescriptorPool descriptorPool = VK_NULL_HANDLE;
    VkResult result = vkCreateDescriptorPool(device, &descriptorPoolCreateInfo, nullptr, &descriptorPool);
    if (result != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkCreateDevice fail");
        return VK_NULL_HANDLE;
    }

    return descriptorPool;
}

}  //namespace ME