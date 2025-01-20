#include "VulkanRHI.h"
#include <set>
#include <array>
#include "MediaEngine/Include/Core/Assert.h"
#include "../RenderLog.h"

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
        m_Swapchain, m_SwapchainImages, m_ImageAcquiredSemaphores, m_RenderCompleteSemaphores, m_PhysicalDevice,
        m_Device, m_GraphicQueue, m_PresentQueue, m_Surface, extend, 2);
    m_GraphicSemaphoreCnt = (uint32_t)m_ImageAcquiredSemaphores.size();

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

    m_SwapchainImages.resize(0);

    vkDestroySwapchainKHR(m_Device, m_Swapchain, VK_NULL_HANDLE);
    m_Swapchain = VK_NULL_HANDLE;

    VkExtent2D extend{width, height};
    bool ret = CreateSwapchainResources(
        m_Swapchain, m_SwapchainImages, m_ImageAcquiredSemaphores, m_RenderCompleteSemaphores, m_PhysicalDevice,
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

Ref<RHITexture2D> VulkanRHI::CreateTexture2D(RHITexture2DCreateDesc desc)
{
    return Ref<RHITexture2D>();
}

bool VulkanRHI::BeginCommandBuffer(Ref<RHICommandBuffer> commandBuffer)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(commandBuffer);

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

bool VulkanRHI::EndCommandBuffer(Ref<RHICommandBuffer> commandBuffer)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(commandBuffer);

    VkResult err = vkEndCommandBuffer(vulkanCmdBuffer->CommandBuffer);
    if (err != VK_SUCCESS)
    {
        ME_ASSERT(false, "vkBeginCommandBuffer fail");
        return false;
    }

    return true;
}

bool VulkanRHI::ClearBackBuffer(Ref<RHICommandBuffer> commandBuffer, float r, float g, float b, float a)
{
    Ref<VulkanRHICommandBuffer> vulkanCmdBuffer = std::dynamic_pointer_cast<VulkanRHICommandBuffer>(commandBuffer);
    VkCommandBuffer cmdBuffer = vulkanCmdBuffer->CommandBuffer;
    VkImage swapchainImage = m_SwapchainImages[m_SwapchainFrameIndex];

    {
        VkImageMemoryBarrier barrier;
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.pNext = nullptr;
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = swapchainImage;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags pipeLineSrcStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        VkPipelineStageFlags pipeLineDstStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        vkCmdPipelineBarrier(cmdBuffer, pipeLineSrcStage, pipeLineDstStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
    }

    VkClearColorValue clearColor;
    clearColor.float32[0] = r;
    clearColor.float32[1] = g;
    clearColor.float32[2] = b;
    clearColor.float32[3] = a;
    VkImageSubresourceRange subresRange;
    subresRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    subresRange.baseMipLevel = 0;
    subresRange.levelCount = 1;
    subresRange.baseArrayLayer = 0;
    subresRange.layerCount = 1;
    vkCmdClearColorImage(cmdBuffer, swapchainImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, &clearColor, 1, &subresRange);

    {
        VkImageMemoryBarrier barrier;
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.pNext = nullptr;
        barrier.srcAccessMask = 0;
        barrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
        barrier.oldLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = swapchainImage;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags pipeLineSrcStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
        VkPipelineStageFlags pipeLineDstStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        vkCmdPipelineBarrier(cmdBuffer, pipeLineSrcStage, pipeLineDstStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);
    }

    return false;
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
    std::vector<VkImage>& swapchainImages,
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

    swapchainImages.clear();
    swapchainImages.resize(swapchainImageCount);
    res = vkGetSwapchainImagesKHR(device, swapchain, &swapchainImageCount, swapchainImages.data());
    if (res != VK_SUCCESS)
    {
        RENDER_LOG_ERROR("vkGetSwapchainImagesKHR fail");
        return false;
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

}  //namespace ME